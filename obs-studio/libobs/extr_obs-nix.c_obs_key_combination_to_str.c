#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dstr {int dummy; } ;
struct TYPE_3__ {int modifiers; scalar_t__ key; } ;
typedef  TYPE_1__ obs_key_combination_t ;

/* Variables and functions */
 int INTERACT_ALT_KEY ; 
 int INTERACT_COMMAND_KEY ; 
 int INTERACT_CONTROL_KEY ; 
 int INTERACT_SHIFT_KEY ; 
 scalar_t__ OBS_KEY_ALT ; 
 scalar_t__ OBS_KEY_CONTROL ; 
 scalar_t__ OBS_KEY_META ; 
 scalar_t__ OBS_KEY_NONE ; 
 scalar_t__ OBS_KEY_SHIFT ; 
 int /*<<< orphan*/  add_combo_key (scalar_t__,struct dstr*) ; 

void obs_key_combination_to_str(obs_key_combination_t combination,
				struct dstr *str)
{
	if ((combination.modifiers & INTERACT_CONTROL_KEY) != 0) {
		add_combo_key(OBS_KEY_CONTROL, str);
	}
	if ((combination.modifiers & INTERACT_COMMAND_KEY) != 0) {
		add_combo_key(OBS_KEY_META, str);
	}
	if ((combination.modifiers & INTERACT_ALT_KEY) != 0) {
		add_combo_key(OBS_KEY_ALT, str);
	}
	if ((combination.modifiers & INTERACT_SHIFT_KEY) != 0) {
		add_combo_key(OBS_KEY_SHIFT, str);
	}
	if (combination.key != OBS_KEY_NONE) {
		add_combo_key(combination.key, str);
	}
}