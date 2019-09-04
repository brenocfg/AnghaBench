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
struct symbol {int /*<<< orphan*/  name; int /*<<< orphan*/  export; struct module* module; struct symbol* next; } ;
struct module {char* name; int /*<<< orphan*/  gpl_compatible; struct symbol* unres; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_for_gpl_usage (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_unused (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct symbol* find_symbol (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void check_exports(struct module *mod)
{
	struct symbol *s, *exp;

	for (s = mod->unres; s; s = s->next) {
		const char *basename;
		exp = find_symbol(s->name);
		if (!exp || exp->module == mod)
			continue;
		basename = strrchr(mod->name, '/');
		if (basename)
			basename++;
		else
			basename = mod->name;
		if (!mod->gpl_compatible)
			check_for_gpl_usage(exp->export, basename, exp->name);
		check_for_unused(exp->export, basename, exp->name);
	}
}