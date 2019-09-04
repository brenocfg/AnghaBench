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
struct symbol {int dummy; } ;
struct gstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ ; 
 char* dialog_input_result ; 
 int /*<<< orphan*/  dialog_input_result_len ; 
 int dialog_inputbox (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct symbol**) ; 
 struct gstr get_relations_str (struct symbol**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_window ; 
 int /*<<< orphan*/  search_help ; 
 int /*<<< orphan*/  show_scroll_win (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_free (struct gstr*) ; 
 int /*<<< orphan*/  str_get (struct gstr*) ; 
 struct gstr str_new () ; 
 int /*<<< orphan*/  str_printf (struct gstr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct symbol** sym_re_search (char*) ; 

__attribute__((used)) static void search_conf(void)
{
	struct symbol **sym_arr;
	struct gstr res;
	struct gstr title;
	char *dialog_input;
	int dres;

	title = str_new();
	str_printf( &title, "Enter (sub)string or regexp to search for "
			      "(with or without \"%s\")", CONFIG_);

again:
	dres = dialog_inputbox(main_window,
			"Search Configuration Parameter",
			str_get(&title),
			"", &dialog_input_result, &dialog_input_result_len);
	switch (dres) {
	case 0:
		break;
	case 1:
		show_scroll_win(main_window,
				"Search Configuration", search_help);
		goto again;
	default:
		str_free(&title);
		return;
	}

	/* strip the prefix if necessary */
	dialog_input = dialog_input_result;
	if (strncasecmp(dialog_input_result, CONFIG_, strlen(CONFIG_)) == 0)
		dialog_input += strlen(CONFIG_);

	sym_arr = sym_re_search(dialog_input);
	res = get_relations_str(sym_arr, NULL);
	free(sym_arr);
	show_scroll_win(main_window,
			"Search Results", str_get(&res));
	str_free(&res);
	str_free(&title);
}