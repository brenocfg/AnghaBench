#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symbol {scalar_t__ type; } ;
struct TYPE_4__ {struct expr* expr; struct symbol* sym; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sym; } ;
struct expr {scalar_t__ type; TYPE_2__ left; TYPE_1__ right; } ;

/* Variables and functions */
 scalar_t__ DEBUG_EXPR ; 
 scalar_t__ E_EQUAL ; 
 scalar_t__ E_NOT ; 
 scalar_t__ E_SYMBOL ; 
 scalar_t__ E_UNEQUAL ; 
 scalar_t__ S_BOOLEAN ; 
 scalar_t__ S_TRISTATE ; 
 struct expr* expr_alloc_comp (scalar_t__,struct symbol*,int /*<<< orphan*/ *) ; 
 struct expr* expr_alloc_symbol (int /*<<< orphan*/ *) ; 
 struct expr* expr_copy (struct expr*) ; 
 scalar_t__ expr_eq (struct expr*,struct expr*) ; 
 int /*<<< orphan*/  expr_fprint (struct expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  symbol_mod ; 
 int /*<<< orphan*/  symbol_no ; 
 int /*<<< orphan*/  symbol_yes ; 

__attribute__((used)) static struct expr *expr_join_or(struct expr *e1, struct expr *e2)
{
	struct expr *tmp;
	struct symbol *sym1, *sym2;

	if (expr_eq(e1, e2))
		return expr_copy(e1);
	if (e1->type != E_EQUAL && e1->type != E_UNEQUAL && e1->type != E_SYMBOL && e1->type != E_NOT)
		return NULL;
	if (e2->type != E_EQUAL && e2->type != E_UNEQUAL && e2->type != E_SYMBOL && e2->type != E_NOT)
		return NULL;
	if (e1->type == E_NOT) {
		tmp = e1->left.expr;
		if (tmp->type != E_EQUAL && tmp->type != E_UNEQUAL && tmp->type != E_SYMBOL)
			return NULL;
		sym1 = tmp->left.sym;
	} else
		sym1 = e1->left.sym;
	if (e2->type == E_NOT) {
		if (e2->left.expr->type != E_SYMBOL)
			return NULL;
		sym2 = e2->left.expr->left.sym;
	} else
		sym2 = e2->left.sym;
	if (sym1 != sym2)
		return NULL;
	if (sym1->type != S_BOOLEAN && sym1->type != S_TRISTATE)
		return NULL;
	if (sym1->type == S_TRISTATE) {
		if (e1->type == E_EQUAL && e2->type == E_EQUAL &&
		    ((e1->right.sym == &symbol_yes && e2->right.sym == &symbol_mod) ||
		     (e1->right.sym == &symbol_mod && e2->right.sym == &symbol_yes))) {
			// (a='y') || (a='m') -> (a!='n')
			return expr_alloc_comp(E_UNEQUAL, sym1, &symbol_no);
		}
		if (e1->type == E_EQUAL && e2->type == E_EQUAL &&
		    ((e1->right.sym == &symbol_yes && e2->right.sym == &symbol_no) ||
		     (e1->right.sym == &symbol_no && e2->right.sym == &symbol_yes))) {
			// (a='y') || (a='n') -> (a!='m')
			return expr_alloc_comp(E_UNEQUAL, sym1, &symbol_mod);
		}
		if (e1->type == E_EQUAL && e2->type == E_EQUAL &&
		    ((e1->right.sym == &symbol_mod && e2->right.sym == &symbol_no) ||
		     (e1->right.sym == &symbol_no && e2->right.sym == &symbol_mod))) {
			// (a='m') || (a='n') -> (a!='y')
			return expr_alloc_comp(E_UNEQUAL, sym1, &symbol_yes);
		}
	}
	if (sym1->type == S_BOOLEAN && sym1 == sym2) {
		if ((e1->type == E_NOT && e1->left.expr->type == E_SYMBOL && e2->type == E_SYMBOL) ||
		    (e2->type == E_NOT && e2->left.expr->type == E_SYMBOL && e1->type == E_SYMBOL))
			return expr_alloc_symbol(&symbol_yes);
	}

	if (DEBUG_EXPR) {
		printf("optimize (");
		expr_fprint(e1, stdout);
		printf(") || (");
		expr_fprint(e2, stdout);
		printf(")?\n");
	}
	return NULL;
}