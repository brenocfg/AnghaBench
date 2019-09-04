#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dstr {int dummy; } ;
typedef  int obs_key_t ;

/* Variables and functions */
#define  OBS_KEY_MOUSE1 173 
#define  OBS_KEY_MOUSE10 172 
#define  OBS_KEY_MOUSE11 171 
#define  OBS_KEY_MOUSE12 170 
#define  OBS_KEY_MOUSE13 169 
#define  OBS_KEY_MOUSE14 168 
#define  OBS_KEY_MOUSE15 167 
#define  OBS_KEY_MOUSE16 166 
#define  OBS_KEY_MOUSE17 165 
#define  OBS_KEY_MOUSE18 164 
#define  OBS_KEY_MOUSE19 163 
#define  OBS_KEY_MOUSE2 162 
#define  OBS_KEY_MOUSE20 161 
#define  OBS_KEY_MOUSE21 160 
#define  OBS_KEY_MOUSE22 159 
#define  OBS_KEY_MOUSE23 158 
#define  OBS_KEY_MOUSE24 157 
#define  OBS_KEY_MOUSE25 156 
#define  OBS_KEY_MOUSE26 155 
#define  OBS_KEY_MOUSE27 154 
#define  OBS_KEY_MOUSE28 153 
#define  OBS_KEY_MOUSE29 152 
#define  OBS_KEY_MOUSE3 151 
#define  OBS_KEY_MOUSE4 150 
#define  OBS_KEY_MOUSE5 149 
#define  OBS_KEY_MOUSE6 148 
#define  OBS_KEY_MOUSE7 147 
#define  OBS_KEY_MOUSE8 146 
#define  OBS_KEY_MOUSE9 145 
#define  OBS_KEY_NUM0 144 
#define  OBS_KEY_NUM1 143 
#define  OBS_KEY_NUM2 142 
#define  OBS_KEY_NUM3 141 
#define  OBS_KEY_NUM4 140 
#define  OBS_KEY_NUM5 139 
#define  OBS_KEY_NUM6 138 
#define  OBS_KEY_NUM7 137 
#define  OBS_KEY_NUM8 136 
#define  OBS_KEY_NUM9 135 
#define  OBS_KEY_NUMASTERISK 134 
#define  OBS_KEY_NUMEQUAL 133 
#define  OBS_KEY_NUMMINUS 132 
#define  OBS_KEY_NUMPERIOD 131 
#define  OBS_KEY_NUMPLUS 130 
#define  OBS_KEY_NUMSLASH 129 
#define  OBS_KEY_SPACE 128 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_get_hotkey_translation (int const,char*) ; 

__attribute__((used)) static bool localized_key_to_str(obs_key_t key, struct dstr *str)
{
#define MAP_KEY(k, s) case k: \
		dstr_copy(str, obs_get_hotkey_translation(k, s)); \
		return true

#define MAP_BUTTON(i) case OBS_KEY_MOUSE ## i: \
		dstr_copy(str, obs_get_hotkey_translation(key, "Mouse " #i)); \
		return true

	switch (key) {
	MAP_KEY(OBS_KEY_SPACE,       "Space");
	MAP_KEY(OBS_KEY_NUMEQUAL,    "= (Keypad)");
	MAP_KEY(OBS_KEY_NUMASTERISK, "* (Keypad)");
	MAP_KEY(OBS_KEY_NUMPLUS,     "+ (Keypad)");
	MAP_KEY(OBS_KEY_NUMMINUS,    "- (Keypad)");
	MAP_KEY(OBS_KEY_NUMPERIOD,   ". (Keypad)");
	MAP_KEY(OBS_KEY_NUMSLASH,    "/ (Keypad)");
	MAP_KEY(OBS_KEY_NUM0,        "0 (Keypad)");
	MAP_KEY(OBS_KEY_NUM1,        "1 (Keypad)");
	MAP_KEY(OBS_KEY_NUM2,        "2 (Keypad)");
	MAP_KEY(OBS_KEY_NUM3,        "3 (Keypad)");
	MAP_KEY(OBS_KEY_NUM4,        "4 (Keypad)");
	MAP_KEY(OBS_KEY_NUM5,        "5 (Keypad)");
	MAP_KEY(OBS_KEY_NUM6,        "6 (Keypad)");
	MAP_KEY(OBS_KEY_NUM7,        "7 (Keypad)");
	MAP_KEY(OBS_KEY_NUM8,        "8 (Keypad)");
	MAP_KEY(OBS_KEY_NUM9,        "9 (Keypad)");

	MAP_BUTTON(1);
	MAP_BUTTON(2);
	MAP_BUTTON(3);
	MAP_BUTTON(4);
	MAP_BUTTON(5);
	MAP_BUTTON(6);
	MAP_BUTTON(7);
	MAP_BUTTON(8);
	MAP_BUTTON(9);
	MAP_BUTTON(10);
	MAP_BUTTON(11);
	MAP_BUTTON(12);
	MAP_BUTTON(13);
	MAP_BUTTON(14);
	MAP_BUTTON(15);
	MAP_BUTTON(16);
	MAP_BUTTON(17);
	MAP_BUTTON(18);
	MAP_BUTTON(19);
	MAP_BUTTON(20);
	MAP_BUTTON(21);
	MAP_BUTTON(22);
	MAP_BUTTON(23);
	MAP_BUTTON(24);
	MAP_BUTTON(25);
	MAP_BUTTON(26);
	MAP_BUTTON(27);
	MAP_BUTTON(28);
	MAP_BUTTON(29);
	default: break;
	}
#undef MAP_BUTTON
#undef MAP_KEY

	return false;
}