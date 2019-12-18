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
struct menu {int /*<<< orphan*/  sym; } ;

/* Variables and functions */
#define  KEY_EXIT 131 
#define  S_HEX 130 
#define  S_INT 129 
#define  S_STRING 128 
 int /*<<< orphan*/  btn_dialog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_input_result ; 
 int /*<<< orphan*/  dialog_input_result_len ; 
 int dialog_inputbox (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* inputbox_instructions_hex ; 
 char* inputbox_instructions_int ; 
 char* inputbox_instructions_string ; 
 int /*<<< orphan*/  main_window ; 
 char* menu_get_prompt (struct menu*) ; 
 int /*<<< orphan*/  show_help (struct menu*) ; 
 int /*<<< orphan*/  sym_get_string_value (int /*<<< orphan*/ ) ; 
 int sym_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_set_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conf_string(struct menu *menu)
{
	const char *prompt = menu_get_prompt(menu);

	while (1) {
		int res;
		const char *heading;

		switch (sym_get_type(menu->sym)) {
		case S_INT:
			heading = inputbox_instructions_int;
			break;
		case S_HEX:
			heading = inputbox_instructions_hex;
			break;
		case S_STRING:
			heading = inputbox_instructions_string;
			break;
		default:
			heading = "Internal nconf error!";
		}
		res = dialog_inputbox(main_window,
				prompt ? prompt : "Main Menu",
				heading,
				sym_get_string_value(menu->sym),
				&dialog_input_result,
				&dialog_input_result_len);
		switch (res) {
		case 0:
			if (sym_set_string_value(menu->sym,
						dialog_input_result))
				return;
			btn_dialog(main_window,
				"You have made an invalid entry.", 0);
			break;
		case 1:
			show_help(menu);
			break;
		case KEY_EXIT:
			return;
		}
	}
}