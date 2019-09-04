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
typedef  int /*<<< orphan*/  u64 ;
struct symbol {scalar_t__ binding; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 scalar_t__ STB_GLOBAL ; 
 struct symbol* dso__first_symbol (struct dso*) ; 
 struct symbol* dso__next_symbol (struct symbol*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static u64 find_entry_trampoline(struct dso *dso)
{
	/* Duplicates are removed so lookup all aliases */
	const char *syms[] = {
		"_entry_trampoline",
		"__entry_trampoline_start",
		"entry_SYSCALL_64_trampoline",
	};
	struct symbol *sym = dso__first_symbol(dso);
	unsigned int i;

	for (; sym; sym = dso__next_symbol(sym)) {
		if (sym->binding != STB_GLOBAL)
			continue;
		for (i = 0; i < ARRAY_SIZE(syms); i++) {
			if (!strcmp(sym->name, syms[i]))
				return sym->start;
		}
	}

	return 0;
}