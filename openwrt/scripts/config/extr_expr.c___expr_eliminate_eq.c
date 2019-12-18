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
struct TYPE_4__ {int /*<<< orphan*/ * sym; struct expr* expr; } ;
struct TYPE_3__ {struct expr* expr; } ;
struct expr {int type; TYPE_2__ left; TYPE_1__ right; } ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  E_AND 129 
#define  E_OR 128 
 scalar_t__ E_SYMBOL ; 
 struct expr* e1 ; 
 struct expr* e2 ; 
 struct expr* expr_alloc_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_eq (struct expr*,struct expr*) ; 
 int /*<<< orphan*/  expr_free (struct expr*) ; 
 int /*<<< orphan*/  symbol_no ; 
 int /*<<< orphan*/  symbol_yes ; 
 int /*<<< orphan*/  trans_count ; 

__attribute__((used)) static void __expr_eliminate_eq(enum expr_type type, struct expr **ep1, struct expr **ep2)
{
	if (e1->type == type) {
		__expr_eliminate_eq(type, &e1->left.expr, &e2);
		__expr_eliminate_eq(type, &e1->right.expr, &e2);
		return;
	}
	if (e2->type == type) {
		__expr_eliminate_eq(type, &e1, &e2->left.expr);
		__expr_eliminate_eq(type, &e1, &e2->right.expr);
		return;
	}
	if (e1->type == E_SYMBOL && e2->type == E_SYMBOL &&
	    e1->left.sym == e2->left.sym &&
	    (e1->left.sym == &symbol_yes || e1->left.sym == &symbol_no))
		return;
	if (!expr_eq(e1, e2))
		return;
	trans_count++;
	expr_free(e1); expr_free(e2);
	switch (type) {
	case E_OR:
		e1 = expr_alloc_symbol(&symbol_no);
		e2 = expr_alloc_symbol(&symbol_no);
		break;
	case E_AND:
		e1 = expr_alloc_symbol(&symbol_yes);
		e2 = expr_alloc_symbol(&symbol_yes);
		break;
	default:
		;
	}
}