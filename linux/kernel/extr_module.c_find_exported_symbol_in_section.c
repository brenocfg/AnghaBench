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
struct symsearch {int start; int stop; } ;
struct module {int dummy; } ;
struct kernel_symbol {int dummy; } ;
struct find_symbol_arg {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct kernel_symbol* bsearch (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ check_exported_symbol (struct symsearch const*,struct module*,struct kernel_symbol*,void*) ; 
 int /*<<< orphan*/  cmp_name ; 

__attribute__((used)) static bool find_exported_symbol_in_section(const struct symsearch *syms,
					    struct module *owner,
					    void *data)
{
	struct find_symbol_arg *fsa = data;
	struct kernel_symbol *sym;

	sym = bsearch(fsa->name, syms->start, syms->stop - syms->start,
			sizeof(struct kernel_symbol), cmp_name);

	if (sym != NULL && check_exported_symbol(syms, owner,
						 sym - syms->start, data))
		return true;

	return false;
}