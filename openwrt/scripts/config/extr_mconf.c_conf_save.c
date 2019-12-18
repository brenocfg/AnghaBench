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
#define  KEY_ESC 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  conf_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dialog_clear () ; 
 int /*<<< orphan*/ * dialog_input_result ; 
 int dialog_inputbox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  save_config_help ; 
 int /*<<< orphan*/  save_config_text ; 
 int /*<<< orphan*/  set_config_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_helptext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_textbox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void conf_save(void)
{
	while (1) {
		int res;
		dialog_clear();
		res = dialog_inputbox(NULL, save_config_text,
				      11, 55, filename);
		switch(res) {
		case 0:
			if (!dialog_input_result[0])
				return;
			if (!conf_write(dialog_input_result)) {
				set_config_filename(dialog_input_result);
				return;
			}
			show_textbox(NULL, _("Can't create file!  Probably a nonexistent directory."), 5, 60);
			break;
		case 1:
			show_helptext(_("Save Alternate Configuration"), save_config_help);
			break;
		case KEY_ESC:
			return;
		}
	}
}