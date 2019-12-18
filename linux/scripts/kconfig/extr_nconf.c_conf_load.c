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

/* Variables and functions */
#define  KEY_EXIT 128 
 int /*<<< orphan*/  btn_dialog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dialog_input_result ; 
 int /*<<< orphan*/  dialog_input_result_len ; 
 int dialog_inputbox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  load_config_help ; 
 int /*<<< orphan*/  load_config_text ; 
 int /*<<< orphan*/  main_window ; 
 int /*<<< orphan*/  set_config_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_scroll_win (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_set_change_count (int) ; 

__attribute__((used)) static void conf_load(void)
{
	while (1) {
		int res;
		res = dialog_inputbox(main_window,
				NULL, load_config_text,
				filename,
				&dialog_input_result,
				&dialog_input_result_len);
		switch (res) {
		case 0:
			if (!dialog_input_result[0])
				return;
			if (!conf_read(dialog_input_result)) {
				set_config_filename(dialog_input_result);
				sym_set_change_count(1);
				return;
			}
			btn_dialog(main_window, "File does not exist!", 0);
			break;
		case 1:
			show_scroll_win(main_window,
					"Load Alternate Configuration",
					load_config_help);
			break;
		case KEY_EXIT:
			return;
		}
	}
}