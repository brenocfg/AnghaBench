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
struct symbol {scalar_t__ binding; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ STB_GLOBAL ; 
 int /*<<< orphan*/  arch__compare_symbol_names (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dso_sym_match(struct symbol *sym, const char *name, int *cnt,
			  int idx)
{
	/* Same name, and global or the n'th found or any */
	return !arch__compare_symbol_names(name, sym->name) &&
	       ((!idx && sym->binding == STB_GLOBAL) ||
		(idx > 0 && ++*cnt == idx) ||
		idx < 0);
}