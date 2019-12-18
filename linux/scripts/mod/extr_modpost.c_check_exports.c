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
struct symbol {int /*<<< orphan*/  name; int /*<<< orphan*/  export; int /*<<< orphan*/  namespace; int /*<<< orphan*/  weak; struct module* module; struct symbol* next; } ;
struct module {char* name; int /*<<< orphan*/  gpl_compatible; int /*<<< orphan*/  required_namespaces; struct symbol* unres; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_namespace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_gpl_usage (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_unused (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct symbol* find_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ have_vmlinux ; 
 int /*<<< orphan*/  merror (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  module_imports_namespace (struct module*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  warn (char*,char const*,char*,...) ; 
 scalar_t__ warn_unresolved ; 
 int /*<<< orphan*/  write_namespace_deps ; 

__attribute__((used)) static int check_exports(struct module *mod)
{
	struct symbol *s, *exp;
	int err = 0;

	for (s = mod->unres; s; s = s->next) {
		const char *basename;
		exp = find_symbol(s->name);
		if (!exp || exp->module == mod) {
			if (have_vmlinux && !s->weak) {
				if (warn_unresolved) {
					warn("\"%s\" [%s.ko] undefined!\n",
					     s->name, mod->name);
				} else {
					merror("\"%s\" [%s.ko] undefined!\n",
					       s->name, mod->name);
					err = 1;
				}
			}
			continue;
		}
		basename = strrchr(mod->name, '/');
		if (basename)
			basename++;
		else
			basename = mod->name;

		if (exp->namespace) {
			add_namespace(&mod->required_namespaces,
				      exp->namespace);

			if (!write_namespace_deps &&
			    !module_imports_namespace(mod, exp->namespace)) {
				warn("module %s uses symbol %s from namespace %s, but does not import it.\n",
				     basename, exp->name, exp->namespace);
			}
		}

		if (!mod->gpl_compatible)
			check_for_gpl_usage(exp->export, basename, exp->name);
		check_for_unused(exp->export, basename, exp->name);
	}

	return err;
}