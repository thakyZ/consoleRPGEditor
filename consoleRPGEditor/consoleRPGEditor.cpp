// consoleRPGEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "cstdlib"
#include "time.h"
#include <fstream>
using namespace std;

bool debug = false; // To be used for debugging
bool permDebug = false; // To turn on debugging if the player doesn't use it.

// Race types.
enum RACE { HUMAN, ELF, DARKELF, ANGEL, MONGREL, SHAMANI, NIBELUNG, UNDEAD };

// Class types.
enum OCC { FIGHTER, CLERIC, THEIF, BARD, ROUGE, TINKER, MAGE };

// Loations types.
enum LOCATION { QUIT, TOWN, FOREST, VIEWSTATS, MONSTER, SAVE, ARMORSMITH, BUYARMOR, SELLARMOR, TAVERN, WEAPONSMITH, BUYWEAPON, SELLWEAPON, CHAPEL, BANK, ALCHIMEST };

// Armors types.
enum ARMOR { LOINCLOTH, CLOTH, LEATHER, CHAIN, PLATE, ANCIENTPLATE, MAGICPLATE, ARCHANEPLATE, IMPERVIUMPLATE };

// Weapons types.
enum WEAPON { FISTS, DAGGER, STAFF, SWORD, ANCIENTBLADE, MAGICBLADE, ARCHANEBLADE, VOIDEXCALIBUR };

// Potions.
enum POTION { HEALTH, MANA, EXP, CHEAT };

// Stats Tree.
struct ATTRIBUTES
{
	unsigned int strength; // The strength stat of the class.
	unsigned int faith; // The faith stat of the class.
	unsigned int dexterity; // The dexterity stat of the class.
	unsigned int insperation; // The insperation stat of the class.
	unsigned int cleverness; // The cleverness stat of the class.
	unsigned int focus; // The focus stat of the class.
};

// The class for the character.
class character
{
	public:
		ATTRIBUTES atts; // The stats that the player has.
		int copper; // The amount of money the player has.
		OCC charClass; // The characters class.
		RACE charRace; // The characters race.
		int hp, hpMax; // The hitpoints for the character.
		int mp, mpMax; // The mana or stamina for the character.
		LOCATION location; // The location the player is at.
		WEAPON weapon; // The weapon the character has.
		ARMOR armor; // The armor the character has.
		int masteries; // The skills level of the player.
		bool cheated; // If the player cheated.

		// Create the character sets.
		character()
		{
		}

		// Set the attributes in one line.
		void setAtts(int tmpStrength, int tmpFaith, int tmpDexterity, int tmpInsperation, int tmpCleverness, int tmpFocus)
		{
			ATTRIBUTES tmpAtts;

			tmpAtts.strength = tmpStrength;
			tmpAtts.faith = tmpFaith;
			tmpAtts.dexterity = tmpDexterity;
			tmpAtts.insperation = tmpInsperation;
			tmpAtts.cleverness = tmpCleverness;
			tmpAtts.focus = tmpFocus;

			atts = tmpAtts;
		}
};

// The player save data class.
class playerSaveData
{
	public:
		int strength; // The strength stat of the class.
		int faith; // The faith stat of the class.
		int dexterity; // The dexterity stat of the class.
		int insperation; // The insperation stat of the class.
		int cleverness; // The cleverness stat of the class.
		int focus; // The focus stat of the class.
		int copper; // The amount of money the player has.
		OCC charClass; // The characters class.
		RACE charRace; // The characters race.
		int hp;
		int hpMax; // The hitpoints for the character.
		int mp;
		int mpMax; // The mana or stamina for the character.
		LOCATION location; // The location the player is at.
		WEAPON weapon; // The weapon the character has.
		ARMOR armor; // The armor the character has.
		int masteries; // The skills level of the player.
		bool cheated; // If the player has cheated.

		// Create the player save data class.
		playerSaveData()
		{
		}

		// Write the character to the player save data class.
		void init(character *tmpChar)
		{
			strength = tmpChar->atts.strength; // Set the strength.
			faith = tmpChar->atts.faith; // Set the faith.
			dexterity = tmpChar->atts.dexterity; // Set the dexterity.
			insperation = tmpChar->atts.insperation; // Set the insperation.
			cleverness = tmpChar->atts.cleverness; // Set the cleverness.
			focus = tmpChar->atts.focus; // Set the focus.
			copper = tmpChar->copper; // Set the copper.
			charClass = tmpChar->charClass; // Set the class.
			charRace = tmpChar->charRace; // Set the race.
			hp = tmpChar->hp; // Set the hp.
			hpMax = tmpChar->hpMax; // Set the max hp.
			mp = tmpChar->mp; // Set the mana.
			mpMax = tmpChar->mpMax; // Set the max mana.
			location = tmpChar->location; // Set the location.
			weapon = tmpChar->weapon; // Set the weapon.
			armor = tmpChar->armor; // Set the armor.
			masteries = tmpChar->masteries; // Set the masteries.
			cheated = tmpChar->cheated;
		}
};

// Display the weapon name by the player's class.
char *displayWeaponName(int tmpWeapon, int tmpCharClass)
{
	switch (tmpCharClass)
	{
		case 0:
			switch (tmpWeapon)
			{
				case 0:
					return "Fists";
					break;
				case 1:
					return "Dagger";
					break;
				case 2:
					return "Staff";
					break;
				case 3:
					return "Sword";
					break;
				case 4:
					return "Ancient Blade";
					break;
				case 5:
					return "Magic Blade";
					break;
				case 6:
					return "Archane Blade";
					break;
				case 7:
					return "Void Excalibur";
					break;
			}
			break;
		case 1:
			switch (tmpWeapon)
			{
				case 0:
					return "Fists";
					break;
				case 1:
					return "Cross";
					break;
				case 2:
					return "Long Cross";
					break;
				case 3:
					return "Holy Cross";
					break;
				case 4:
					return "Ancient Cross";
					break;
				case 5:
					return "Magic Cross";
					break;
				case 6:
					return "Archane Cross";
					break;
				case 7:
					return "Void Cross";
					break;
			}
			break;
		case 2:
			switch (tmpWeapon)
			{
				case 0:
					return "Fists";
					break;
				case 1:
					return "Rusty Dagger";
					break;
				case 2:
					return "Dagger";
					break;
				case 3:
					return "Barbed Dagger";
					break;
				case 4:
					return "Ancient Dagger";
					break;
				case 5:
					return "Magic Dagger";
					break;
				case 6:
					return "Archane Dagger";
					break;
				case 7:
					return "Void Dagger";
					break;
			}
			break;
		case 3:
			switch (tmpWeapon)
			{
				case 0:
					return "Butter Knife";
					break;
				case 1:
					return "Rusty Sharp Knife";
					break;
				case 2:
					return "Sharp Knife";
					break;
				case 3:
					return "Barbed Knife";
					break;
				case 4:
					return "Ancient Knife";
					break;
				case 5:
					return "Magic Knife";
					break;
				case 6:
					return "Archane Knife";
					break;
				case 7:
					return "Void Long Knife";
					break;
			}
			break;
		case 4:
			switch (tmpWeapon)
			{
				case 0:
					return "Fists";
					break;
				case 1:
					return "Rusty Short Blade";
					break;
				case 2:
					return "Short Balde";
					break;
				case 3:
					return "Barbed Short Blade";
					break;
				case 4:
					return "Ancient Short Blade";
					break;
				case 5:
					return "Magic Short Blade";
					break;
				case 6:
					return "Archane Short Blade";
					break;
				case 7:
					return "Void Short Excalibur";
					break;
			}
			break;
		case 5:
			switch (tmpWeapon)
			{
				case 0:
					return "Fists";
					break;
				case 1:
					return "Rusty Wrench";
					break;
				case 2:
					return "Wrench";
					break;
				case 3:
					return "Mechanical Wrench";
					break;
				case 4:
					return "Ancient Wrench";
					break;
				case 5:
					return "Magic Wrench";
					break;
				case 6:
					return "Archane Wrench";
					break;
				case 7:
					return "Void Wrench";
					break;
			}
			break;
		case 6:
			switch (tmpWeapon)
			{
				case 0:
					return "Fists";
					break;
				case 1:
					return "Dagger";
					break;
				case 2:
					return "Staff";
					break;
				case 3:
					return "Sword";
					break;
				case 4:
					return "Ancient Blade";
					break;
				case 5:
					return "Magic Blade";
					break;
				case 6:
					return "Archane Blade";
					break;
				case 7:
					return "Void Excalibur";
					break;
			}
			break;
		case 7:
			switch (tmpWeapon)
			{
				case 0:
					return "Fists";
					break;
				case 1:
					return "Dagger";
					break;
				case 2:
					return "Staff";
					break;
				case 3:
					return "Sword";
					break;
				case 4:
					return "Ancient Staff";
					break;
				case 5:
					return "Magic Staff";
					break;
				case 6:
					return "Archane Staff";
					break;
				case 7:
					return "Void Staff";
					break;
			}
			break;
	}

	return "";
}

// Display the armor name by the player's class.
char *displayArmorName(int tmpArmor, int tmpCharClass)
{
	switch (tmpCharClass)
	{
		case 0:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			switch (tmpArmor)
			{
				case 0:
					return "Loin Cloth";
					break;
				case 1:
					return "Cloth Armor";
					break;
				case 2:
					return "Leather Armor";
					break;
				case 3:
					return "Chain Armor";
					break;
				case 4:
					return "Plate Armor";
					break;
				case 5:
					return "Ancient Plate Armor";
					break;
				case 6:
					return "Magic Plate Armor";
					break;
				case 7:
					return "Archane Plate Armor";
					break;
				case 8:
					return "Impervium Plate Armor";
					break;
			}
			break;
		case 1:
		case 7:
			switch (tmpArmor)
			{
				case 0:
					return "Loin Cloth";
					break;
				case 1:
					return "Cloth Robe";
					break;
				case 2:
					return "Leather Robe";
					break;
				case 3:
					return "Chain Robe";
					break;
				case 4:
					return "Iron Robe";
					break;
				case 5:
					return "Ancient Robe";
					break;
				case 6:
					return "Magic Robe";
					break;
				case 7:
					return "Archane Robe";
					break;
				case 8:
					return "Impervium Robe";
					break;
			}
			break;
	}

	return "";
}

// Debug the save file.
void debugSave(playerSaveData tmpSaveFile)
{
	cout << "+=================================+\n";
	cout << "   Debug -> STARTING\n";
	cout << "+=================================+\n";
	cout << "Player Save Data: " << ((char *)&tmpSaveFile) << "\n";
	cout << "Player Save Size: " << (sizeof(tmpSaveFile)) << "\n";
	cout << "+=================================+\n";
	cout << "   Save Class Debug\n";
	cout << "+=================================+\n";

	cout << "Stats:\n";
	cout << "   Strength:      " << tmpSaveFile.strength << "\n";
	cout << "   Faith:         " << tmpSaveFile.faith << "\n";
	cout << "   Dexterity:     " << tmpSaveFile.dexterity << "\n";
	cout << "   Insperation:   " << tmpSaveFile.insperation << "\n";
	cout << "   Cleverness:    " << tmpSaveFile.cleverness << "\n";
	cout << "   Focus:         " << tmpSaveFile.focus << "\n";
	cout << "Copper:           " << tmpSaveFile.copper << "\n";

	switch (tmpSaveFile.charClass)
	{
		case FIGHTER:
			cout << "Class:            FIGHTER\n";
			break;
		case CLERIC:
			cout << "Class:            CLERIC\n";
			break;
		case ROUGE:
			cout << "Class:            ROUGE\n";
			break;
		case BARD:
			cout << "Class:            BARD\n";
			break;
		case THEIF:
			cout << "Class:            THEIF\n";
			break;
		case TINKER:
			cout << "Class:            TINKER\n";
			break;
		case MAGE:
			cout << "Class:            MAGE\n";
			break;
		default:
			cout << "Class:            BROKEN\n";
			break;
	}

	switch (tmpSaveFile.charRace)
	{
		case HUMAN:
			cout << "Race:             HUMAN\n";
			break;
		case ELF:
			cout << "Race:             ELF\n";
			break;
		case DARKELF:
			cout << "Race:             DARKELF\n";
			break;
		case ANGEL:
			cout << "Race:             ANGEL\n";
			break;
		case MONGREL:
			cout << "Race:             MONGREL\n";
			break;
		case SHAMANI:
			cout << "Race:             SHAMANI\n";
			break;
		case NIBELUNG:
			cout << "Race:             NIBELUNG\n";
			break;
		case UNDEAD:
			cout << "Race:             UNDEAD\n";
			break;
		default:
			cout << "Race:             BROKEN\n";
			break;
	}

	cout << "Hitpoints:        " << tmpSaveFile.hp << "\n";
	cout << "Max Hitpoints:    " << tmpSaveFile.hpMax << "\n";
	cout << "Mana:             " << tmpSaveFile.mp << "\n";
	cout << "Max Mana:         " << tmpSaveFile.mpMax << "\n";

	switch (tmpSaveFile.location)
	{
		case QUIT:
			cout << "Location:         QUIT\n";
			break;
		case VIEWSTATS:
			cout << "Location:         VIEWSTATS\n";
			break;
		case TOWN:
			cout << "Location:         TOWN\n";
			break;
		case FOREST:
			cout << "Location:         FOREST\n";
			break;
		case MONSTER:
			cout << "Location:         MONSTER\n";
			break;
		case SAVE:
			cout << "Location:         SAVE\n";
			break;
		case ARMORSMITH:
			cout << "Location:         ARMORSMITH\n";
			break;
		case BUYARMOR:
			cout << "Location:         BUYARMOR\n";
			break;
		case SELLARMOR:
			cout << "Location:         SELLARMOR\n";
			break;
		case TAVERN:
			cout << "Location:         TAVERN\n";
			break;
		case WEAPONSMITH:
			cout << "Location:         WEAPONSMITH\n";
			break;
		case CHAPEL:
			cout << "Location:         CHAPEL\n";
			break;
		case BANK:
			cout << "Location:         BANK\n";
			break;
		case ALCHIMEST:
			cout << "Location:         ALCHIMEST\n";
			break;
		default:
			cout << "Location:         BROKEN\n";
	}

	switch (tmpSaveFile.weapon)
	{
		case FISTS:
			cout << "Weapon:           FISTS\n";
			break;
		case DAGGER:
			cout << "Weapon:           DAGGER\n";
			break;
		case SWORD:
			cout << "Weapon:           SWORD\n";
			break;
		case STAFF:
			cout << "Weapon:           STAFF\n";
			break;
		case ANCIENTBLADE:
			cout << "Weapon:           ANCIENTBLADE\n";
			break;
		case MAGICBLADE:
			cout << "Weapon:           MAGICBLADE\n";
			break;
		case ARCHANEBLADE:
			cout << "Weapon:           ARCHANEBLADE\n";
			break;
		case VOIDEXCALIBUR:
			cout << "Weapon:           VOIDEXCALIBUR\n";
			break;
		default:
			cout << "Weapon:           BROKEN\n";
	}

	cout << "Weapon set name:  " << displayWeaponName(tmpSaveFile.weapon, tmpSaveFile.charClass) << "\n";

	switch (tmpSaveFile.armor)
	{
		case LOINCLOTH:
			cout << "Armor:            LOINCLOTH\n";
			break;
		case CLOTH:
			cout << "Armor:            CLOTH\n";
			break;
		case LEATHER:
			cout << "Armor:            LEATHER\n";
			break;
		case CHAIN:
			cout << "Armor:            CHAIN\n";
			break;
		case PLATE:
			cout << "Armor:            PLATE\n";
			break;
		case ANCIENTPLATE:
			cout << "Armor:            ANCIENTPLATE\n";
			break;
		case MAGICPLATE:
			cout << "Armor:            MAGICPLATE\n";
			break;
		case ARCHANEPLATE:
			cout << "Armor:            ARCHANEPLATE\n";
			break;
		case IMPERVIUMPLATE:
			cout << "Armor:            IMPERVIUMPLATE\n";
			break;
		default:
			cout << "Armor:            BROKEN\n";
	}

	cout << "Armor set name:   " << displayArmorName(tmpSaveFile.armor, tmpSaveFile.charClass) << "\n";

	cout << "Masteries:        " << tmpSaveFile.masteries << "\n";

	switch (tmpSaveFile.cheated)
	{
		case true:
			cout << "Cheated:         TRUE\n";
			break;
		case false:
			cout << "Cheated:         FALSE\n";
			break;
	}

	cout << "+=================================+\n";
	cout << "   Debug -> ENDED\n";
	cout << "+=================================+\n";
}

// Write to the save file.
void writeToFile(character *tmpChar)
{
	// Create the var for the save file.
	ofstream myfile;

	// The temp Player save data;
	playerSaveData playerSave;

	// Initlize the player save.
	playerSave.init(tmpChar);

	if (playerSave.copper >= 25000 && !debug && !permDebug)
	{
		playerSave.copper = 24999;
	}

	// Open the save file.
	myfile.open("./save1.sav",'w');

	// Write to the save file.
	myfile.write((char *)&playerSave, sizeof(playerSave));

	// If debug is enabled.
	if (debug)
	{
		debugSave(playerSave);
	}
	// Close the file after we are done with it.
	myfile.close();

	cout << "File saved.\n";
}

// Load from the save file.
character getFromFile()
{
	// The character var for the loaded file.
	playerSaveData playerSave;

	// The temp character
	character tmpChar;

	// Load the save file.
	ifstream myfile("./save1.sav", ios::binary);

	// Read the save file.
	myfile.read((char *)&playerSave, sizeof(playerSave));

	LOCATION location = playerSave.location;
	int strength = playerSave.strength; // The strength stat of the class.
	int faith = playerSave.faith; // The faith stat of the class.
	int dexterity = playerSave.dexterity; // The dexterity stat of the class.
	int insperation =  playerSave.insperation; // The insperation stat of the class.
	int cleverness = playerSave.cleverness; // The cleverness stat of the class.
	int focus = playerSave.focus; // The focus stat of the class.
	int copper = playerSave.copper; // The amount of money the player has.
	OCC charClass = playerSave.charClass; // The characters class.
	RACE charRace = playerSave.charRace; // The characters race.
	int hp = playerSave.hp; // The hitpoints for the character.
	int hpMax = playerSave.hpMax; // The max hitpoints for the character.
	int mp = playerSave.mp; // The mana or stamina for the character.
	int mpMax = playerSave.mpMax; // The max mana or stamina for the character.
	WEAPON weapon = playerSave.weapon; // The weapon the character has.
	ARMOR armor = playerSave.armor; // The armor the character has.
	int masteries = playerSave.masteries; // The skills level of the player.
	bool cheated = playerSave.cheated; // If the player has cheated

	tmpChar.location  = location;
	tmpChar.setAtts(strength, cleverness, dexterity, faith, focus, insperation);
	tmpChar.charClass = charClass;
	tmpChar.copper = copper;
	tmpChar.hp = hp;
	tmpChar.mp = mp;
	tmpChar.masteries = masteries;
	tmpChar.hpMax = hpMax;
	tmpChar.mpMax = mpMax;
	tmpChar.charRace = charRace;
	tmpChar.weapon = weapon;
	tmpChar.armor = armor;
	tmpChar.cheated = cheated;

	// Debug the class.
	if (debug)
	{
		debugSave(playerSave);
	}

	// Close the file when we are done with it.
	myfile.close();

	cout << "Save loaded.\n";

	// Return the character to return the char.
	return tmpChar;
}

// Display the save table.
void displaySave(character player1)
{
	cout << "\n";
	cout << "Player Save File: \n\n";

	cout << "+------+--------------------+------------------------\n";
	cout << "| [#]  | Property           | Value    \n";
	cout << "+------+--------------------+------------------------\n";
	cout << "| [--] | Attributes:        |          \n";
	cout << "| [1]  |    Strength:       | " << player1.atts.strength << "\n";
	cout << "| [2]  |    Cleverness:     | " << player1.atts.cleverness << "\n";
	cout << "| [3]  |    Dexterity:      | " << player1.atts.dexterity << "\n";
	cout << "| [4]  |    Faith:          | " << player1.atts.faith << "\n";
	cout << "| [5]  |    Focus:          | " << player1.atts.focus << "\n";
	cout << "| [6]  |    Insperation:    | " << player1.atts.insperation << "\n";
	cout << "| [7]  | Copper:            | " << player1.copper << "\n";
	cout << "| [8]  | Hitpoints:         | " << player1.hp << "\n";
	cout << "| [9]  | Max Hitpoints:     | " << player1.hpMax << "\n";
	cout << "| [10] | Mana/Stamina:      | " << player1.mp << "\n";
	cout << "| [11] | Max Mana/Stamina:  | " << player1.mpMax << "\n";
	cout << "| [12] | Masteries:         | " << player1.masteries << "\n";
	cout << "| [13] | Location:          | ";
	switch (player1.location)
	{
		case QUIT:
			cout << "QUIT";
			break;
		case TOWN:
			cout << "TOWN";
			break;
		case FOREST:
			cout << "FOREST";
			break;
		case VIEWSTATS:
			cout << "VIEWSTATS";
			break;
		case MONSTER:
			cout << "MONSTER";
			break;
		case SAVE:
			cout << "SAVE";
			break;
		case ARMORSMITH:
			cout << "ARMORSMITH";
			break;
		case BUYARMOR:
			cout << "BUYARMOR";
			break;
		case SELLARMOR:
			cout << "SELLARMOR";
			break;
		case TAVERN:
			cout << "TAVERN";
			break;
		case WEAPONSMITH:
			cout << "WEAPONSMITH";
			break;
		case BUYWEAPON:
			cout << "BUYWEAPON";
			break;
		case SELLWEAPON:
			cout << "SELLWEAPON";
			break;
		case CHAPEL:
			cout << "CHAPEL";
			break;
		case BANK:
			cout << "BANK";
			break;
		case ALCHIMEST:
			cout << "ALCHIMEST";
			break;
	}
	cout << "\n";
	cout << "| [14] | Class:             | ";
	switch (player1.charClass)
	{
		case FIGHTER:
			cout << "FIGHTER";
			break;
		case CLERIC:
			cout << "CLERIC";
			break;
		case THEIF:
			cout << "THEIF";
			break;
		case BARD:
			cout << "BARD";
			break;
		case ROUGE:
			cout << "ROUGE";
			break;
		case TINKER:
			cout << "TINKER";
			break;
		case MAGE:
			cout << "MAGE";
			break;
	}
	cout << "\n";
	cout << "| [15] | Race:              | ";
	switch (player1.charRace)
	{
		case HUMAN:
			cout << "HUMAN";
			break;
		case ELF:
			cout << "ELF";
			break;
		case DARKELF:
			cout << "DARKELF";
			break;
		case ANGEL:
			cout << "ANGEL";
			break;
		case MONGREL:
			cout << "MONGREL";
			break;
		case SHAMANI:
			cout << "SHAMANI";
			break;
		case NIBELUNG:
			cout << "NIBELUNG";
			break;
		case UNDEAD:
			cout << "UNDEAD";
			break;
	}
	cout << "\n";
	cout << "| [16] | Weapon:            | ";
	switch (player1.weapon)
	{
		case FISTS:
			cout << "FISTS";
			break;
		case DAGGER:
			cout << "DAGGER";
			break;
		case STAFF:
			cout << "STAFF";
			break;
		case SWORD:
			cout << "SWORD";
			break;
		case ANCIENTBLADE:
			cout << "ANCIENTBLADE";
			break;
		case MAGICBLADE:
			cout << "MAGICBLADE";
			break;
		case ARCHANEBLADE:
			cout << "ARCHANEBLADE";
			break;
		case VOIDEXCALIBUR:
			cout << "VOIDEXCALIBUR";
			break;
	}
	cout << "\n";
	cout << "| [--] |    Weapon-Class:   | " << displayWeaponName(player1.weapon, player1.charClass) << "\n";
	cout << "| [17] | Armor:             | ";
	switch (player1.armor)
	{
		case LOINCLOTH:
			cout << "LOINCLOTH";
			break;
		case CLOTH:
			cout << "CLOTH";
			break;
		case LEATHER:
			cout << "LEATHER";
			break;
		case CHAIN:
			cout << "CHAIN";
			break;
		case PLATE:
			cout << "PLATE";
			break;
		case ANCIENTPLATE:
			cout << "ANCIENTPLATE";
			break;
		case MAGICPLATE:
			cout << "MAGICPLATE";
			break;
		case ARCHANEPLATE:
			cout << "ARCHANEPLATE";
			break;
		case IMPERVIUMPLATE:
			cout << "IMPERVIUMPLATE";
			break;
	}
	cout << "\n";
	cout << "| [--] | Armor-Class:       | " << displayArmorName(player1.armor, player1.charClass) << "\n";
	cout << "| [18] | Cheated:           | ";
	switch (player1.cheated)
	{
		case true:
			cout << "TRUE";
			break;
		case false:
			cout << "FALSE";
			break;
	}
	cout << "\n";
	cout << "+------+--------------------+------------------------\n";
	cout << "| [19] | Done               |\n";
	cout << "+------+--------------------+------------------------\n";
}

// Load the save.
void loadSave()
{
	character player1 = getFromFile(); // Start up the player editor.
	int menuItem = 0; // The option to choose what to edit.
	char saveItem; // To choose to save or not.
	int valueItem = 0; // To change the value of an option.
	bool reroll = true; // If the player changes a value or doesnt input correctly.

	// Start the loop.
	while (reroll)
	{
		reroll = false; // end the loop.

		menuItem = 0; // Set the default when going back to displaying the table.
		valueItem = 0; // Set the default when going back to displaying the table.

		// Display the save table.
		displaySave(player1);

		cout << "\n";
		cout << "Choose from the selected: [1] to [19]\n";
		cout << "Please input the correct input when editing a property.\n";
		cout << "   If you don't it'll break the save...\n";

		// Get which number the user chooses.
		cin >> menuItem;

		cout << "\n\n";

		// Choose from which number the user chooses.
		switch (menuItem)
		{
			case 1: // Strength
				cout << "This value has to be a NUMBER.\nStrength = ";
				cin >> valueItem;
				player1.atts.strength = (int)valueItem;
				cout << "   Strength = " << player1.atts.strength << "\n";
				reroll = true;
				break;
			case 2: // Cleverness
				cout << "This value has to be a NUMBER.\nCleverness = ";
				cin >> valueItem;
				player1.atts.cleverness = (int)valueItem;
				cout << "   Cleverness = " << player1.atts.cleverness << "\n";
				reroll = true;
				break;
			case 3: // Dexterity
				cout << "This value has to be a NUMBER.\nDexterity = ";
				cin >> valueItem;
				player1.atts.dexterity = (int)valueItem;
				cout << "   Dexterity = " << player1.atts.dexterity << "\n";
				reroll = true;
				break;
			case 4: // Faith
				cout << "This value has to be a NUMBER.\nFaith = ";
				cin >> valueItem;
				player1.atts.faith = (int)valueItem;
				cout << "   Faith = " << player1.atts.faith << "\n";
				reroll = true;
				break;
			case 5: // Focus
				cout << "This value has to be a NUMBER.\nFocus = ";
				cin >> valueItem;
				player1.atts.focus = (int)valueItem;
				cout << "   Focus = " << player1.atts.focus << "\n";
				reroll = true;
				break;
			case 6: // Insperation
				cout << "This value has to be a NUMBER.\nInsperation = ";
				cin >> valueItem;
				player1.atts.insperation = (int)valueItem;
				cout << "   Insperation = " << player1.atts.insperation << "\n";
				reroll = true;
				break;
			case 7: // Copper
				cout << "This value has to be a NUMBER.\nCopper = ";
				cin >> valueItem;
				player1.copper = (int)valueItem;
				cout << "   Copper = " << player1.copper << "\n";
				reroll = true;
				break;
			case 8: // Hitpoints
				cout << "This value has to be a NUMBER.\nHitpoints = ";
				cin >> valueItem;
				player1.hp = (int)valueItem;
				cout << "   Hitpoints = " << player1.hp << "\n";
				reroll = true;
				break;
			case 9: // Max Hitpoints
				cout << "This value has to be a NUMBER.\nMax Hitpoints = ";
				cin >> valueItem;
				player1.hpMax = (int)valueItem;
				cout << "   Max Hitpoints = " << player1.hpMax << "\n";
				reroll = true;
				break;
			case 10: // Mana/Stamina
				cout << "This value has to be a NUMBER.\nMana/Stamina = ";
				cin >> valueItem;
				player1.mp = (int)valueItem;
				cout << "   Mana/Stamina = " << player1.mp << "\n";
				reroll = true;
				break;
			case 11: // Max Mana/Stamina
				cout << "This value has to be a NUMBER.\nMax Mana/Stamina = ";
				cin >> valueItem;
				player1.mpMax = (int)valueItem;
				cout << "   Max Mana/Stamina = " << player1.mpMax << "\n";
				reroll = true;
				break;
			case 12: // Masteries
				cout << "This value has to be a NUMBER.\nMasteries = ";
				cin >> valueItem;
				player1.masteries = (int)valueItem;
				cout << "   Masteries = " << player1.masteries << "\n";
				reroll = true;
				break;
			case 13: // Location
				cout << "This value has to be a NUMBER.\nQUIT=0,TOWN=1,FOREST=2,VIEWSTATS=3,MONSTER=4,SAVE=5,\nARMORSMITH=6,BUYARMOR=7,SELLARMOR=8,TAVERN=9,\nWEAPONSMITH=10,BUYWEAPON=11,SELLWEAPON=12,CHAPEL=13,\nBANK=14,ALCHIMEST=15\nLocation = ";
				cin >> valueItem;
				switch (valueItem)
				{
					case 0:
						player1.location = QUIT;
						break;
					case 1:
						player1.location = TOWN;
						break;
					case 2:
						player1.location = FOREST;
						break;
					case 3:
						player1.location = VIEWSTATS;
						break;
					case 4:
						player1.location = MONSTER;
						break;
					case 5:
						player1.location = SAVE;
						break;
					case 6:
						player1.location = ARMORSMITH;
						break;
					case 7:
						player1.location = BUYARMOR;
						break;
					case 8:
						player1.location = SELLARMOR;
						break;
					case 9:
						player1.location = TAVERN;
						break;
					case 10:
						player1.location = WEAPONSMITH;
						break;
					case 11:
						player1.location = BUYWEAPON;
						break;
					case 12:
						player1.location = SELLWEAPON;
						break;
					case 13:
						player1.location = CHAPEL;
						break;
					case 14:
						player1.location = BANK;
						break;
					case 15:
						player1.location = ALCHIMEST;
						break;
				}
				cout << "\n";
				cout << "   Location = ";
				switch (player1.location)
				{
					case QUIT:
						cout << "QUIT";
						break;
					case TOWN:
						cout << "TOWN";
						break;
					case FOREST:
						cout << "FOREST";
						break;
					case VIEWSTATS:
						cout << "VIEWSTATS";
						break;
					case MONSTER:
						cout << "MONSTER";
						break;
					case SAVE:
						cout << "SAVE";
						break;
					case ARMORSMITH:
						cout << "ARMORSMITH";
						break;
					case BUYARMOR:
						cout << "BUYARMOR";
						break;
					case SELLARMOR:
						cout << "SELLARMOR";
						break;
					case TAVERN:
						cout << "TAVERN";
						break;
					case WEAPONSMITH:
						cout << "WEAPONSMITH";
						break;
					case BUYWEAPON:
						cout << "BUYWEAPON";
						break;
					case SELLWEAPON:
						cout << "SELLWEAPON";
						break;
					case CHAPEL:
						cout << "CHAPEL";
						break;
					case BANK:
						cout << "BANK";
						break;
					case ALCHIMEST:
						cout << "ALCHIMEST";
						break;
				}
				cout << "\n";
				reroll = true;
				break;
			case 14: // Class
				cout << "This value has to be a NUMBER.\nFIGHTER=0,CLERIC=1,THEIF=2,BARD=3,ROUGE=4,TINKER=5,\nMAGE=6\nClass = ";
				cin >> valueItem;
				switch (valueItem)
				{
					default:
					case 0:
						player1.charClass = FIGHTER;
						break;
					case 1:
						player1.charClass = CLERIC;
						break;
					case 2:
						player1.charClass = THEIF;
						break;
					case 3:
						player1.charClass = BARD;
						break;
					case 4:
						player1.charClass = ROUGE;
						break;
					case 5:
						player1.charClass = TINKER;
						break;
					case 6:
						player1.charClass = MAGE;
						break;
				}
				cout << "\n";
				cout << "   Class = ";
				switch (player1.charClass)
				{
					case FIGHTER:
						cout << "FIGHTER";
						break;
					case CLERIC:
						cout << "CLERIC";
						break;
					case THEIF:
						cout << "THEIF";
						break;
					case BARD:
						cout << "BARD";
						break;
					case ROUGE:
						cout << "ROUGE";
						break;
					case TINKER:
						cout << "TINKER";
						break;
					case MAGE:
						cout << "MAGE";
						break;
				}
				cout << "\n";
				reroll = true;
				break;
			case 15: // Race
				cout << "This value has to be a NUMBER.\nHUMAN=0,ELF=1,DARKELF=2,ANGEL=3,MONGREL=4,SHAMANI=5\nNIBELUNG=6,UNDEAD=7\nRace = ";
				cin >> valueItem;
				switch (valueItem)
				{
					default:
					case 0:
						player1.charRace = HUMAN;
						break;
					case 1:
						player1.charRace = ELF;
						break;
					case 2:
						player1.charRace = DARKELF;
						break;
					case 3:
						player1.charRace = ANGEL;
						break;
					case 4:
						player1.charRace = MONGREL;
						break;
					case 5:
						player1.charRace = SHAMANI;
						break;
					case 6:
						player1.charRace = NIBELUNG;
						break;
					case 7:
						player1.charRace = UNDEAD;
						break;
				}
				cout << "\n";
				cout << "   Race = ";
				switch (player1.charRace)
				{
					case HUMAN:
						cout << "HUMAN";
						break;
					case ELF:
						cout << "ELF";
						break;
					case DARKELF:
						cout << "DARKELF";
						break;
					case ANGEL:
						cout << "ANGEL";
						break;
					case MONGREL:
						cout << "MONGREL";
						break;
					case SHAMANI:
						cout << "SHAMANI";
						break;
					case NIBELUNG:
						cout << "NIBELUNG";
						break;
					case UNDEAD:
						cout << "UNDEAD";
						break;
				}
				cout << "\n";
				reroll = true;
				break;
			case 16: // Weapon
				cout << "This value has to be a NUMBER.\nFISTS=0,DAGGER=1,STAFF=2,SWORD=3,ANCIENTBLADE=4,MAGICBLADE=5,\nARCHANEBLADE=6,VOIDEXCALIBUR=7\nWeapon = ";
				cin >> valueItem;
				switch (valueItem)
				{
					default:
					case 0:
						player1.weapon = FISTS;
						break;
					case 1:
						player1.weapon = DAGGER;
						break;
					case 2:
						player1.weapon = STAFF;
						break;
					case 3:
						player1.weapon = SWORD;
						break;
					case 4:
						player1.weapon = ANCIENTBLADE;
						break;
					case 5:
						player1.weapon = MAGICBLADE;
						break;
					case 6:
						player1.weapon = ARCHANEBLADE;
						break;
					case 7:
						player1.weapon = VOIDEXCALIBUR;
						break;
				}
				cout << "\n";
				cout << "   Weapon = ";
				switch (player1.weapon)
				{
					case FISTS:
						cout << "FISTS";
						break;
					case DAGGER:
						cout << "DAGGER";
						break;
					case STAFF:
						cout << "STAFF";
						break;
					case SWORD:
						cout << "SWORD";
						break;
					case ANCIENTBLADE:
						cout << "ANCIENTBLADE";
						break;
					case MAGICBLADE:
						cout << "MAGICBLADE";
						break;
					case ARCHANEBLADE:
						cout << "ARCHANEBLADE";
						break;
					case VOIDEXCALIBUR:
						cout << "VOIDEXCALIBUR";
						break;
				}
				cout << "\n";
				reroll = true;
				break;
			case 17: // Armor
				cout << "This value has to be a NUMBER.\nLOINCLOTH=0,CLOTH=1,LEATHER=2,CHAIN=3,PLATE=4,\nANCIENTPLATE=5,MAGICPLATE=6,ARCHANEPLATE=7,\nIMPERVIUMPLATE=8\nWeapon = ";
				cin >> valueItem;
				switch (valueItem)
				{
					default:
					case 0:
						player1.armor = LOINCLOTH;
						break;
					case 1:
						player1.armor = CLOTH;
						break;
					case 2:
						player1.armor = LEATHER;
						break;
					case 3:
						player1.armor = CHAIN;
						break;
					case 4:
						player1.armor = PLATE;
						break;
					case 5:
						player1.armor = ANCIENTPLATE;
						break;
					case 6:
						player1.armor = MAGICPLATE;
						break;
					case 7:
						player1.armor = ARCHANEPLATE;
						break;
					case 8:
						player1.armor = IMPERVIUMPLATE;
						break;
				}
				cout << "\n";
				cout << "   Armor = ";
				switch (player1.armor)
				{
					case LOINCLOTH:
						cout << "LOINCLOTH";
						break;
					case CLOTH:
						cout << "CLOTH";
						break;
					case LEATHER:
						cout << "LEATHER";
						break;
					case CHAIN:
						cout << "CHAIN";
						break;
					case PLATE:
						cout << "PLATE";
						break;
					case ANCIENTPLATE:
						cout << "ANCIENTPLATE";
						break;
					case MAGICPLATE:
						cout << "MAGICPLATE";
						break;
					case ARCHANEPLATE:
						cout << "ARCHANEPLATE";
						break;
					case IMPERVIUMPLATE:
						cout << "IMPERVIUMPLATE";
						break;
				}
				cout << "\n";
				reroll = true;
				break;
			case 18: // Cheated
				cout << "This value has to be a NUMBER.\nFALSE=0,TRUE=1\nCheated = ";
				cin >> valueItem;
				switch (valueItem)
				{
					default:
					case 0:
						player1.cheated = false;
						break;
					case 1:
						player1.cheated = true;
						break;
				}
				cout << "\n";
				cout << "   Cheated = ";
				switch (player1.cheated)
				{
					case true:
						cout << "TRUE";
						break;
					case false:
						cout << "FALSE";
						break;
				}
				cout << "\n";
				reroll = true;
				break;
			case 19: // "Done."
				cout << "Are you sure you want to save and exit? [Y]es [N]o\n";
				cin >> saveItem;
				switch (saveItem)
				{
					case 'y':
					case 'Y':
						reroll = false;
						break;
					case 'n':
					case 'N':
						reroll = false;
						break;
					default:
						reroll = true;
						break;
				}
				cout << "\n\n";
				if (saveItem == 'y' || saveItem == 'Y')
				{
					writeToFile(&player1);
				}
				break;
		}
	}
}

// Display the about screen
void displayAbout()
{
	cout << "\n";
	cout << "+------------------------------------------------------------+\n";
	cout << "|                                                            |\n";
	cout << "|  consoleRPGEditor                                          |\n";
	cout << "|  Created By: Nire Inicana                                  |\n";
	cout << "|  Website: https://github.com/TZCraft-NSR/consoleRPGEditor  |\n";
	cout << "|  Copyright (c) 2014 TZCraft NSR                            |\n";
	cout << "|  Licence: MIT                                              |\n";
	cout << "|                                                            |\n";
	cout << "+------------------------------------------------------------+\n";
	cout << "\n\n";
}

// The main startup of the file
int _tmain(int argc, _TCHAR* argv[])
{
	bool reroll = true; // The bool of if the user doesn't input the right input.
	char menuItem; // The choice of which option to choose.

	cout << "Welcome to the consoleRPG Editor!\n";
	cout << "\n";
	cout << "NOTE: Please place this in the same folder as save1.sav!\n";
	cout << "\n";

	while (reroll)
	{
		reroll = false;

		cout << "[L]oad 'save1.sav'\t[A]bout consoleRPGEditor\n[Q]uit";
		cout << "\n";

		cin >> menuItem;

		cout << "\n";

		switch (menuItem)
		{
			case 'l':
			case 'L':
				loadSave();
				reroll = true;
				break;
			case 'a':
			case 'A':
				displayAbout();
				reroll = true;
				break;
			case 'q':
			case 'Q':
				reroll = false;
				break;
			default:
				if (menuItem != '6' && !permDebug)
				{
					cout << "Please choose a correct input.\n\n";
					reroll = true;
				}
				break;
		}

		if (menuItem == '6' && permDebug)
		{
			debug = true;

			cout << "\n";
			cout << "+=================================+\n";
			cout << "   Debug -> ENABLED\n";
			cout << "+=================================+\n";
			cout << "\n";

			reroll = true;
		}
	}
	return 0;
}