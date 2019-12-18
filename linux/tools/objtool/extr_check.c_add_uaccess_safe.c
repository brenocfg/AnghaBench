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
struct symbol {int uaccess_safe; } ;
struct objtool_file {int /*<<< orphan*/  elf; } ;

/* Variables and functions */
 struct symbol* find_symbol_by_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  uaccess ; 
 char** uaccess_safe_builtin ; 

__attribute__((used)) static void add_uaccess_safe(struct objtool_file *file)
{
	struct symbol *func;
	const char **name;

	if (!uaccess)
		return;

	for (name = uaccess_safe_builtin; *name; name++) {
		func = find_symbol_by_name(file->elf, *name);
		if (!func)
			continue;

		func->uaccess_safe = true;
	}
}