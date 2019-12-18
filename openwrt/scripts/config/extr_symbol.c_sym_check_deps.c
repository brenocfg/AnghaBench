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
struct symbol {int flags; } ;
struct property {int dummy; } ;
struct dep_stack {int dummy; } ;

/* Variables and functions */
 int SYMBOL_CHECK ; 
 int SYMBOL_CHECKED ; 
 int /*<<< orphan*/  dep_stack_insert (struct dep_stack*,struct symbol*) ; 
 int /*<<< orphan*/  dep_stack_remove () ; 
 struct symbol* prop_get_symbol (struct property*) ; 
 struct symbol* sym_check_choice_deps (struct symbol*) ; 
 int /*<<< orphan*/  sym_check_print_recursive (struct symbol*) ; 
 struct symbol* sym_check_sym_deps (struct symbol*) ; 
 struct property* sym_get_choice_prop (struct symbol*) ; 
 scalar_t__ sym_is_choice (struct symbol*) ; 
 scalar_t__ sym_is_choice_value (struct symbol*) ; 

struct symbol *sym_check_deps(struct symbol *sym)
{
	struct symbol *sym2;
	struct property *prop;

	if (sym->flags & SYMBOL_CHECK) {
		sym_check_print_recursive(sym);
		return sym;
	}
	if (sym->flags & SYMBOL_CHECKED)
		return NULL;

	if (sym_is_choice_value(sym)) {
		struct dep_stack stack;

		/* for choice groups start the check with main choice symbol */
		dep_stack_insert(&stack, sym);
		prop = sym_get_choice_prop(sym);
		sym2 = sym_check_deps(prop_get_symbol(prop));
		dep_stack_remove();
	} else if (sym_is_choice(sym)) {
		sym2 = sym_check_choice_deps(sym);
	} else {
		sym->flags |= (SYMBOL_CHECK | SYMBOL_CHECKED);
		sym2 = sym_check_sym_deps(sym);
		sym->flags &= ~SYMBOL_CHECK;
	}

	if (sym2 && sym2 == sym)
		sym2 = NULL;

	return sym2;
}