#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  expr; } ;
struct TYPE_8__ {int /*<<< orphan*/  expr; } ;
struct TYPE_7__ {int /*<<< orphan*/  expr; } ;
struct symbol {char* name; TYPE_5__ implied; TYPE_3__ rev_dep; TYPE_2__ dir_dep; struct property* prop; } ;
struct property {int lineno; int /*<<< orphan*/  type; TYPE_4__* file; struct menu* menu; struct property* next; } ;
struct menu {int lineno; TYPE_1__* file; } ;
struct dep_stack {int /*<<< orphan*/ * expr; struct symbol* sym; struct property* prop; struct dep_stack* next; struct dep_stack* prev; } ;
struct TYPE_9__ {char* name; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 struct dep_stack* check_top ; 
 int /*<<< orphan*/  dep_stack_insert (struct dep_stack*,struct symbol*) ; 
 int /*<<< orphan*/  dep_stack_remove () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct symbol* prop_get_symbol (int /*<<< orphan*/ ) ; 
 char* prop_get_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sym_get_choice_prop (struct symbol*) ; 
 scalar_t__ sym_is_choice (struct symbol*) ; 
 scalar_t__ sym_is_choice_value (struct symbol*) ; 

__attribute__((used)) static void sym_check_print_recursive(struct symbol *last_sym)
{
	struct dep_stack *stack;
	struct symbol *sym, *next_sym;
	struct menu *menu = NULL;
	struct property *prop;
	struct dep_stack cv_stack;

	if (sym_is_choice_value(last_sym)) {
		dep_stack_insert(&cv_stack, last_sym);
		last_sym = prop_get_symbol(sym_get_choice_prop(last_sym));
	}

	for (stack = check_top; stack != NULL; stack = stack->prev)
		if (stack->sym == last_sym)
			break;
	if (!stack) {
		fprintf(stderr, "unexpected recursive dependency error\n");
		return;
	}

	for (; stack; stack = stack->next) {
		sym = stack->sym;
		next_sym = stack->next ? stack->next->sym : last_sym;
		prop = stack->prop;
		if (prop == NULL)
			prop = stack->sym->prop;

		/* for choice values find the menu entry (used below) */
		if (sym_is_choice(sym) || sym_is_choice_value(sym)) {
			for (prop = sym->prop; prop; prop = prop->next) {
				menu = prop->menu;
				if (prop->menu)
					break;
			}
		}
		if (stack->sym == last_sym)
			fprintf(stderr, "%s:%d:error: recursive dependency detected!\n",
				prop->file->name, prop->lineno);

		if (sym_is_choice(sym)) {
			fprintf(stderr, "%s:%d:\tchoice %s contains symbol %s\n",
				menu->file->name, menu->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} else if (sym_is_choice_value(sym)) {
			fprintf(stderr, "%s:%d:\tsymbol %s is part of choice %s\n",
				menu->file->name, menu->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} else if (stack->expr == &sym->dir_dep.expr) {
			fprintf(stderr, "%s:%d:\tsymbol %s depends on %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} else if (stack->expr == &sym->rev_dep.expr) {
			fprintf(stderr, "%s:%d:\tsymbol %s is selected by %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} else if (stack->expr == &sym->implied.expr) {
			fprintf(stderr, "%s:%d:\tsymbol %s is implied by %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				next_sym->name ? next_sym->name : "<choice>");
		} else if (stack->expr) {
			fprintf(stderr, "%s:%d:\tsymbol %s %s value contains %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				prop_get_type_name(prop->type),
				next_sym->name ? next_sym->name : "<choice>");
		} else {
			fprintf(stderr, "%s:%d:\tsymbol %s %s is visible depending on %s\n",
				prop->file->name, prop->lineno,
				sym->name ? sym->name : "<choice>",
				prop_get_type_name(prop->type),
				next_sym->name ? next_sym->name : "<choice>");
		}
	}

	fprintf(stderr,
		"For a resolution refer to Documentation/kbuild/kconfig-language.rst\n"
		"subsection \"Kconfig recursive dependency limitations\"\n"
		"\n");

	if (check_top == &cv_stack)
		dep_stack_remove();
}