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
struct module {int /*<<< orphan*/  name; } ;
struct load_info {int dummy; } ;
struct kernel_symbol {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 char* get_modinfo (struct load_info const*,char*) ; 
 char* get_next_modinfo (struct load_info const*,char*,char*) ; 
 int /*<<< orphan*/  kernel_symbol_name (struct kernel_symbol const*) ; 
 char* kernel_symbol_namespace (struct kernel_symbol const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pr_warn (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int verify_namespace_is_imported(const struct load_info *info,
					const struct kernel_symbol *sym,
					struct module *mod)
{
	const char *namespace;
	char *imported_namespace;

	namespace = kernel_symbol_namespace(sym);
	if (namespace) {
		imported_namespace = get_modinfo(info, "import_ns");
		while (imported_namespace) {
			if (strcmp(namespace, imported_namespace) == 0)
				return 0;
			imported_namespace = get_next_modinfo(
				info, "import_ns", imported_namespace);
		}
#ifdef CONFIG_MODULE_ALLOW_MISSING_NAMESPACE_IMPORTS
		pr_warn(
#else
		pr_err(
#endif
			"%s: module uses symbol (%s) from namespace %s, but does not import it.\n",
			mod->name, kernel_symbol_name(sym), namespace);
#ifndef CONFIG_MODULE_ALLOW_MISSING_NAMESPACE_IMPORTS
		return -EINVAL;
#endif
	}
	return 0;
}