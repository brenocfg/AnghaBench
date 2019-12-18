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
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  E_AND 129 
#define  E_OR 128 
 struct expr* e1 ; 
 struct expr* e2 ; 
 struct expr* expr_alloc_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_free (struct expr*) ; 
 struct expr* expr_join_and (struct expr*,struct expr*) ; 
 struct expr* expr_join_or (struct expr*,struct expr*) ; 
 int /*<<< orphan*/  symbol_no ; 
 int /*<<< orphan*/  symbol_yes ; 
 int /*<<< orphan*/  trans_count ; 

__attribute__((used)) static void expr_eliminate_dups1(enum expr_type type, struct expr **ep1, struct expr **ep2)
{
#define e1 (*ep1)
#define e2 (*ep2)
	struct expr *tmp;

	/* Recurse down to leaves */

	if (e1->type == type) {
		expr_eliminate_dups1(type, &e1->left.expr, &e2);
		expr_eliminate_dups1(type, &e1->right.expr, &e2);
		return;
	}
	if (e2->type == type) {
		expr_eliminate_dups1(type, &e1, &e2->left.expr);
		expr_eliminate_dups1(type, &e1, &e2->right.expr);
		return;
	}

	/* e1 and e2 are leaves. Compare and process them. */

	if (e1 == e2)
		return;

	switch (e1->type) {
	case E_OR: case E_AND:
		expr_eliminate_dups1(e1->type, &e1, &e1);
	default:
		;
	}

	switch (type) {
	case E_OR:
		tmp = expr_join_or(e1, e2);
		if (tmp) {
			expr_free(e1); expr_free(e2);
			e1 = expr_alloc_symbol(&symbol_no);
			e2 = tmp;
			trans_count++;
		}
		break;
	case E_AND:
		tmp = expr_join_and(e1, e2);
		if (tmp) {
			expr_free(e1); expr_free(e2);
			e1 = expr_alloc_symbol(&symbol_yes);
			e2 = tmp;
			trans_count++;
		}
		break;
	default:
		;
	}
#undef e1
#undef e2
}