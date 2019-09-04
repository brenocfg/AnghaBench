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
typedef  int /*<<< orphan*/  t ;
struct obs_hotkeys_translations {char* numpad_num; char const* mouse_num; scalar_t__ numpad_decimal; scalar_t__ numpad_plus; scalar_t__ numpad_minus; scalar_t__ numpad_multiply; scalar_t__ numpad_divide; scalar_t__ escape; scalar_t__ space; scalar_t__ menu; scalar_t__ meta; scalar_t__ control; scalar_t__ alt; scalar_t__ shift; scalar_t__ pause; scalar_t__ print; scalar_t__ tab; scalar_t__ backspace; scalar_t__ caps_lock; scalar_t__ scroll_lock; scalar_t__ num_lock; scalar_t__ page_down; scalar_t__ page_up; scalar_t__ end; scalar_t__ home; scalar_t__ del; scalar_t__ insert; int /*<<< orphan*/  member_0; } ;
struct dstr {scalar_t__ array; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_KEY_ALT ; 
 int /*<<< orphan*/  OBS_KEY_BACKSPACE ; 
 int /*<<< orphan*/  OBS_KEY_CAPSLOCK ; 
 int /*<<< orphan*/  OBS_KEY_CONTROL ; 
 int /*<<< orphan*/  OBS_KEY_DELETE ; 
 int /*<<< orphan*/  OBS_KEY_END ; 
 int /*<<< orphan*/  OBS_KEY_ESCAPE ; 
 int /*<<< orphan*/  OBS_KEY_HOME ; 
 int /*<<< orphan*/  OBS_KEY_INSERT ; 
 int /*<<< orphan*/  OBS_KEY_MENU ; 
 int /*<<< orphan*/  OBS_KEY_META ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE1 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE10 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE11 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE12 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE13 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE14 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE15 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE16 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE17 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE18 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE19 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE2 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE20 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE21 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE22 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE23 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE24 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE25 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE26 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE27 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE28 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE29 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE3 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE4 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE5 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE6 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE7 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE8 ; 
 int /*<<< orphan*/  OBS_KEY_MOUSE9 ; 
 int /*<<< orphan*/  OBS_KEY_NUM0 ; 
 int /*<<< orphan*/  OBS_KEY_NUM1 ; 
 int /*<<< orphan*/  OBS_KEY_NUM2 ; 
 int /*<<< orphan*/  OBS_KEY_NUM3 ; 
 int /*<<< orphan*/  OBS_KEY_NUM4 ; 
 int /*<<< orphan*/  OBS_KEY_NUM5 ; 
 int /*<<< orphan*/  OBS_KEY_NUM6 ; 
 int /*<<< orphan*/  OBS_KEY_NUM7 ; 
 int /*<<< orphan*/  OBS_KEY_NUM8 ; 
 int /*<<< orphan*/  OBS_KEY_NUM9 ; 
 int /*<<< orphan*/  OBS_KEY_NUMASTERISK ; 
 int /*<<< orphan*/  OBS_KEY_NUMLOCK ; 
 int /*<<< orphan*/  OBS_KEY_NUMMINUS ; 
 int /*<<< orphan*/  OBS_KEY_NUMPERIOD ; 
 int /*<<< orphan*/  OBS_KEY_NUMPLUS ; 
 int /*<<< orphan*/  OBS_KEY_NUMSLASH ; 
 int /*<<< orphan*/  OBS_KEY_PAGEDOWN ; 
 int /*<<< orphan*/  OBS_KEY_PAGEUP ; 
 int /*<<< orphan*/  OBS_KEY_PAUSE ; 
 int /*<<< orphan*/  OBS_KEY_PRINT ; 
 int /*<<< orphan*/  OBS_KEY_SCROLLLOCK ; 
 int /*<<< orphan*/  OBS_KEY_SHIFT ; 
 int /*<<< orphan*/  OBS_KEY_SPACE ; 
 int /*<<< orphan*/  OBS_KEY_TAB ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_depad (struct dstr*) ; 
 int /*<<< orphan*/ * dstr_find (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  memcpy (struct obs_hotkeys_translations*,struct obs_hotkeys_translations*,size_t) ; 
 int /*<<< orphan*/  obs_set_key_translation (int /*<<< orphan*/ ,scalar_t__) ; 

void obs_hotkeys_set_translations_s(
		struct obs_hotkeys_translations *translations, size_t size)
{
#define ADD_TRANSLATION(key_name, var_name) \
	if (t.var_name) \
		obs_set_key_translation(key_name, t.var_name);

	struct obs_hotkeys_translations t = {0};
	struct dstr numpad = {0};
	struct dstr mouse = {0};
	struct dstr button = {0};

	if (!translations) {
		return;
	}

	memcpy(&t, translations, (size < sizeof(t)) ? size : sizeof(t));

	ADD_TRANSLATION(OBS_KEY_INSERT, insert);
	ADD_TRANSLATION(OBS_KEY_DELETE, del);
	ADD_TRANSLATION(OBS_KEY_HOME, home);
	ADD_TRANSLATION(OBS_KEY_END, end);
	ADD_TRANSLATION(OBS_KEY_PAGEUP, page_up);
	ADD_TRANSLATION(OBS_KEY_PAGEDOWN, page_down);
	ADD_TRANSLATION(OBS_KEY_NUMLOCK, num_lock);
	ADD_TRANSLATION(OBS_KEY_SCROLLLOCK, scroll_lock);
	ADD_TRANSLATION(OBS_KEY_CAPSLOCK, caps_lock);
	ADD_TRANSLATION(OBS_KEY_BACKSPACE, backspace);
	ADD_TRANSLATION(OBS_KEY_TAB, tab);
	ADD_TRANSLATION(OBS_KEY_PRINT, print);
	ADD_TRANSLATION(OBS_KEY_PAUSE, pause);
	ADD_TRANSLATION(OBS_KEY_SHIFT, shift);
	ADD_TRANSLATION(OBS_KEY_ALT, alt);
	ADD_TRANSLATION(OBS_KEY_CONTROL, control);
	ADD_TRANSLATION(OBS_KEY_META, meta);
	ADD_TRANSLATION(OBS_KEY_MENU, menu);
	ADD_TRANSLATION(OBS_KEY_SPACE, space);
	ADD_TRANSLATION(OBS_KEY_ESCAPE, escape);
#ifdef __APPLE__
	const char *numpad_str = t.apple_keypad_num;
	ADD_TRANSLATION(OBS_KEY_NUMSLASH, apple_keypad_divide);
	ADD_TRANSLATION(OBS_KEY_NUMASTERISK, apple_keypad_multiply);
	ADD_TRANSLATION(OBS_KEY_NUMMINUS, apple_keypad_minus);
	ADD_TRANSLATION(OBS_KEY_NUMPLUS, apple_keypad_plus);
	ADD_TRANSLATION(OBS_KEY_NUMPERIOD, apple_keypad_decimal);
	ADD_TRANSLATION(OBS_KEY_NUMEQUAL, apple_keypad_equal);
#else
	const char *numpad_str = t.numpad_num;
	ADD_TRANSLATION(OBS_KEY_NUMSLASH, numpad_divide);
	ADD_TRANSLATION(OBS_KEY_NUMASTERISK, numpad_multiply);
	ADD_TRANSLATION(OBS_KEY_NUMMINUS, numpad_minus);
	ADD_TRANSLATION(OBS_KEY_NUMPLUS, numpad_plus);
	ADD_TRANSLATION(OBS_KEY_NUMPERIOD, numpad_decimal);
#endif

	if (numpad_str) {
		dstr_copy(&numpad, numpad_str);
		dstr_depad(&numpad);

		if (dstr_find(&numpad, "%1") == NULL) {
			dstr_cat(&numpad, " %1");
		}

#define ADD_NUMPAD_NUM(idx) \
		dstr_copy_dstr(&button, &numpad); \
		dstr_replace(&button, "%1", #idx); \
		obs_set_key_translation(OBS_KEY_NUM ## idx, button.array)

		ADD_NUMPAD_NUM(0);
		ADD_NUMPAD_NUM(1);
		ADD_NUMPAD_NUM(2);
		ADD_NUMPAD_NUM(3);
		ADD_NUMPAD_NUM(4);
		ADD_NUMPAD_NUM(5);
		ADD_NUMPAD_NUM(6);
		ADD_NUMPAD_NUM(7);
		ADD_NUMPAD_NUM(8);
		ADD_NUMPAD_NUM(9);
	}

	if (t.mouse_num) {
		dstr_copy(&mouse, t.mouse_num);
		dstr_depad(&mouse);

		if (dstr_find(&mouse, "%1") == NULL) {
			dstr_cat(&mouse, " %1");
		}

#define ADD_MOUSE_NUM(idx) \
		dstr_copy_dstr(&button, &mouse); \
		dstr_replace(&button, "%1", #idx); \
		obs_set_key_translation(OBS_KEY_MOUSE ## idx, button.array)

		ADD_MOUSE_NUM(1);
		ADD_MOUSE_NUM(2);
		ADD_MOUSE_NUM(3);
		ADD_MOUSE_NUM(4);
		ADD_MOUSE_NUM(5);
		ADD_MOUSE_NUM(6);
		ADD_MOUSE_NUM(7);
		ADD_MOUSE_NUM(8);
		ADD_MOUSE_NUM(9);
		ADD_MOUSE_NUM(10);
		ADD_MOUSE_NUM(11);
		ADD_MOUSE_NUM(12);
		ADD_MOUSE_NUM(13);
		ADD_MOUSE_NUM(14);
		ADD_MOUSE_NUM(15);
		ADD_MOUSE_NUM(16);
		ADD_MOUSE_NUM(17);
		ADD_MOUSE_NUM(18);
		ADD_MOUSE_NUM(19);
		ADD_MOUSE_NUM(20);
		ADD_MOUSE_NUM(21);
		ADD_MOUSE_NUM(22);
		ADD_MOUSE_NUM(23);
		ADD_MOUSE_NUM(24);
		ADD_MOUSE_NUM(25);
		ADD_MOUSE_NUM(26);
		ADD_MOUSE_NUM(27);
		ADD_MOUSE_NUM(28);
		ADD_MOUSE_NUM(29);
	}

	dstr_free(&numpad);
	dstr_free(&mouse);
	dstr_free(&button);
}