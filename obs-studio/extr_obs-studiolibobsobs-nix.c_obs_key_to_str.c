#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t num; int /*<<< orphan*/ * array; } ;
struct keycode_list {TYPE_2__ list; } ;
struct dstr {int dummy; } ;
typedef  size_t obs_key_t ;
struct TYPE_7__ {struct keycode_list* keycodes; } ;
typedef  TYPE_3__ obs_hotkeys_platform_t ;
struct TYPE_5__ {TYPE_3__* platform_context; scalar_t__* translations; } ;
struct TYPE_8__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
#define  OBS_KEY_ALT 156 
#define  OBS_KEY_BACKSPACE 155 
#define  OBS_KEY_CAPSLOCK 154 
#define  OBS_KEY_CONTROL 153 
#define  OBS_KEY_DELETE 152 
#define  OBS_KEY_DOWN 151 
#define  OBS_KEY_END 150 
#define  OBS_KEY_ESCAPE 149 
 size_t OBS_KEY_F1 ; 
 size_t OBS_KEY_F35 ; 
#define  OBS_KEY_HOME 148 
#define  OBS_KEY_INSERT 147 
#define  OBS_KEY_LEFT 146 
#define  OBS_KEY_MENU 145 
#define  OBS_KEY_META 144 
 size_t OBS_KEY_MOUSE1 ; 
 size_t OBS_KEY_MOUSE29 ; 
 size_t OBS_KEY_NONE ; 
 size_t OBS_KEY_NUM0 ; 
 size_t OBS_KEY_NUM9 ; 
#define  OBS_KEY_NUMASTERISK 143 
#define  OBS_KEY_NUMCOMMA 142 
#define  OBS_KEY_NUMLOCK 141 
#define  OBS_KEY_NUMPERIOD 140 
#define  OBS_KEY_NUMPLUS 139 
#define  OBS_KEY_NUMSLASH 138 
#define  OBS_KEY_PAGEDOWN 137 
#define  OBS_KEY_PAGEUP 136 
#define  OBS_KEY_PAUSE 135 
#define  OBS_KEY_PRINT 134 
#define  OBS_KEY_RIGHT 133 
#define  OBS_KEY_SCROLLLOCK 132 
#define  OBS_KEY_SHIFT 131 
#define  OBS_KEY_SPACE 130 
#define  OBS_KEY_TAB 129 
#define  OBS_KEY_UP 128 
 void dstr_copy (struct dstr*,scalar_t__) ; 
 scalar_t__ dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,int) ; 
 scalar_t__ get_key_translation (struct dstr*,int /*<<< orphan*/ ) ; 
 TYPE_4__* obs ; 
 scalar_t__ obs_get_hotkey_translation (size_t,char*) ; 
 scalar_t__ obs_key_to_name (size_t) ; 

void obs_key_to_str(obs_key_t key, struct dstr *dstr)
{
	if (key >= OBS_KEY_MOUSE1 && key <= OBS_KEY_MOUSE29) {
		if (obs->hotkeys.translations[key]) {
			dstr_copy(dstr, obs->hotkeys.translations[key]);
		} else {
			dstr_printf(dstr, "Mouse %d",
					(int)(key - OBS_KEY_MOUSE1 + 1));
		}
		return;
	}

	if (key >= OBS_KEY_NUM0 && key <= OBS_KEY_NUM9) {
		if (obs->hotkeys.translations[key]) {
			dstr_copy(dstr, obs->hotkeys.translations[key]);
		} else {
			dstr_printf(dstr, "Numpad %d",
					(int)(key - OBS_KEY_NUM0));
		}
		return;
	}

#define translate_key(key, def) \
	dstr_copy(dstr, obs_get_hotkey_translation(key, def))

	switch (key) {
	case OBS_KEY_INSERT:       return translate_key(key, "Insert");
	case OBS_KEY_DELETE:       return translate_key(key, "Delete");
	case OBS_KEY_HOME:         return translate_key(key, "Home");
	case OBS_KEY_END:          return translate_key(key, "End");
	case OBS_KEY_PAGEUP:       return translate_key(key, "Page Up");
	case OBS_KEY_PAGEDOWN:     return translate_key(key, "Page Down");
	case OBS_KEY_NUMLOCK:      return translate_key(key, "Num Lock");
	case OBS_KEY_SCROLLLOCK:   return translate_key(key, "Scroll Lock");
	case OBS_KEY_CAPSLOCK:     return translate_key(key, "Caps Lock");
	case OBS_KEY_BACKSPACE:    return translate_key(key, "Backspace");
	case OBS_KEY_TAB:          return translate_key(key, "Tab");
	case OBS_KEY_PRINT:        return translate_key(key, "Print");
	case OBS_KEY_PAUSE:        return translate_key(key, "Pause");
	case OBS_KEY_LEFT:         return translate_key(key, "Left");
	case OBS_KEY_RIGHT:        return translate_key(key, "Right");
	case OBS_KEY_UP:           return translate_key(key, "Up");
	case OBS_KEY_DOWN:         return translate_key(key, "Down");
	case OBS_KEY_SHIFT:        return translate_key(key, "Shift");
	case OBS_KEY_ALT:          return translate_key(key, "Alt");
	case OBS_KEY_CONTROL:      return translate_key(key, "Control");
	case OBS_KEY_META:         return translate_key(key, "Super");
	case OBS_KEY_MENU:         return translate_key(key, "Menu");
	case OBS_KEY_NUMASTERISK:  return translate_key(key, "Numpad *");
	case OBS_KEY_NUMPLUS:      return translate_key(key, "Numpad +");
	case OBS_KEY_NUMCOMMA:     return translate_key(key, "Numpad ,");
	case OBS_KEY_NUMPERIOD:    return translate_key(key, "Numpad .");
	case OBS_KEY_NUMSLASH:     return translate_key(key, "Numpad /");
	case OBS_KEY_SPACE:        return translate_key(key, "Space");
	case OBS_KEY_ESCAPE:       return translate_key(key, "Escape");
	default:;
	}

	if (key >= OBS_KEY_F1 && key <= OBS_KEY_F35) {
		dstr_printf(dstr, "F%d",
				(int)(key - OBS_KEY_F1 + 1));
		return;
	}

	obs_hotkeys_platform_t *context = obs->hotkeys.platform_context;
	struct keycode_list *keycodes = &context->keycodes[key];

	for (size_t i = 0; i < keycodes->list.num; i++) {
		if (get_key_translation(dstr, keycodes->list.array[i])) {
			break;
		}
	}

	if (key != OBS_KEY_NONE && dstr_is_empty(dstr)) {
		dstr_copy(dstr, obs_key_to_name(key));
	}
}