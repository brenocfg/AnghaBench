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
struct TYPE_4__ {struct expr* expr; } ;
struct TYPE_3__ {struct expr* expr; } ;
struct expr {int type; TYPE_2__ right; TYPE_1__ left; } ;

/* Variables and functions */
#define  E_AND 129 
#define  E_OR 128 
 struct expr* expr_alloc_and (struct expr*,struct expr*) ; 
 struct expr* expr_copy (struct expr*) ; 
 struct expr* expr_eliminate_dups (struct expr*) ; 
 int /*<<< orphan*/  expr_eq (struct expr*,struct expr*) ; 
 int /*<<< orphan*/  expr_free (struct expr*) ; 
 struct expr* expr_get_leftmost_symbol (struct expr*) ; 

struct expr *expr_simplify_unmet_dep(struct expr *e1, struct expr *e2)
{
	struct expr *ret;

	switch (e1->type) {
	case E_OR:
		return expr_alloc_and(
		    expr_simplify_unmet_dep(e1->left.expr, e2),
		    expr_simplify_unmet_dep(e1->right.expr, e2));
	case E_AND: {
		struct expr *e;
		e = expr_alloc_and(expr_copy(e1), expr_copy(e2));
		e = expr_eliminate_dups(e);
		ret = (!expr_eq(e, e1)) ? e1 : NULL;
		expr_free(e);
		break;
		}
	default:
		ret = e1;
		break;
	}

	return expr_get_leftmost_symbol(ret);
}