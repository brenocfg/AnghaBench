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
struct symbol {scalar_t__ name; } ;
struct menu {struct symbol* sym; } ;
struct gstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ ; 
 int /*<<< orphan*/  get_symbol_str (struct gstr*,struct symbol*,int /*<<< orphan*/ *) ; 
 char* menu_get_help (struct menu*) ; 
 scalar_t__ menu_has_help (struct menu*) ; 
 char* nohelp_text ; 
 int /*<<< orphan*/  str_printf (struct gstr*,char*,char const*,...) ; 

void menu_get_ext_help(struct menu *menu, struct gstr *help)
{
	struct symbol *sym = menu->sym;
	const char *help_text = nohelp_text;

	if (menu_has_help(menu)) {
		if (sym->name)
			str_printf(help, "%s%s:\n\n", CONFIG_, sym->name);
		help_text = menu_get_help(menu);
	}
	str_printf(help, "%s\n", help_text);
	if (sym)
		get_symbol_str(help, sym, NULL);
}