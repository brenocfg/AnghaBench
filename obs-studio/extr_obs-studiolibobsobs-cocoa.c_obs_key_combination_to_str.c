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
struct dstr {char* array; scalar_t__ len; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {scalar_t__ key; int modifiers; } ;
typedef  TYPE_1__ obs_key_combination_t ;

/* Variables and functions */
 int INTERACT_ALT_KEY ; 
 int INTERACT_COMMAND_KEY ; 
 int INTERACT_CONTROL_KEY ; 
 int INTERACT_SHIFT_KEY ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 scalar_t__ OBS_KEY_NONE ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int,int) ; 
 char* cmd_str ; 
 char* ctrl_str ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_move (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  init_utf_8_strings ; 
 int /*<<< orphan*/  obs_key_to_str (scalar_t__,struct dstr*) ; 
 char* opt_str ; 
 int pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* shift_str ; 
 int /*<<< orphan*/  strings_token ; 

void obs_key_combination_to_str(obs_key_combination_t key, struct dstr *str)
{
	struct dstr key_str = {0};
	if (key.key != OBS_KEY_NONE)
		obs_key_to_str(key.key, &key_str);

	int res = pthread_once(&strings_token, init_utf_8_strings);
	if (res) {
		blog(LOG_ERROR, "hotkeys-cocoa: Error while translating "
				"modifiers %d (0x%x)", res, res);
		dstr_move(str, &key_str);
		return;
	}

#define CHECK_MODIFIER(mod, str) ((key.modifiers & mod) ? str : "")
	dstr_printf(str, "%s%s%s%s%s",
			CHECK_MODIFIER(INTERACT_CONTROL_KEY, ctrl_str),
			CHECK_MODIFIER(INTERACT_ALT_KEY, opt_str),
			CHECK_MODIFIER(INTERACT_SHIFT_KEY, shift_str),
			CHECK_MODIFIER(INTERACT_COMMAND_KEY, cmd_str),
			key_str.len ? key_str.array : "");
#undef CHECK_MODIFIER

	dstr_free(&key_str);
}