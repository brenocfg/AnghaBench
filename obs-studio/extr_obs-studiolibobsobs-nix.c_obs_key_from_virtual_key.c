#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const xcb_keysym_t ;
typedef  int /*<<< orphan*/  xcb_keycode_t ;
typedef  int /*<<< orphan*/  obs_key_t ;
struct TYPE_6__ {scalar_t__* keysyms; int syms_per_code; int num_keysyms; scalar_t__ min_keycode; } ;
typedef  TYPE_2__ obs_hotkeys_platform_t ;
struct TYPE_5__ {TYPE_2__* platform_context; } ;
struct TYPE_7__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_KEY_NONE ; 
 int /*<<< orphan*/  key_from_keycode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* obs ; 

obs_key_t obs_key_from_virtual_key(int sym)
{
	obs_hotkeys_platform_t *context = obs->hotkeys.platform_context;
	const xcb_keysym_t *keysyms = context->keysyms;
	int syms_per_code = context->syms_per_code;
	int num_keysyms = context->num_keysyms;

	if (sym == 0)
		return OBS_KEY_NONE;

	for (int i = 0; i < num_keysyms; i++) {
		if (keysyms[i] == (xcb_keysym_t)sym) {
			xcb_keycode_t code = (xcb_keycode_t)(i / syms_per_code);
			code += context->min_keycode;
			obs_key_t key = key_from_keycode(context, code);

			return key;
		}
	}

	return OBS_KEY_NONE;
}