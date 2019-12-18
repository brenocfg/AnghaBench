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
struct symbol {int dummy; } ;
struct TYPE_4__ {struct expr* expr; struct symbol* sym; } ;
struct TYPE_3__ {struct symbol* sym; struct expr* expr; } ;
struct expr {int type; TYPE_2__ left; TYPE_1__ right; } ;

/* Variables and functions */
#define  E_AND 137 
#define  E_EQUAL 136 
#define  E_GEQ 135 
#define  E_GTH 134 
#define  E_LEQ 133 
#define  E_LTH 132 
#define  E_NOT 131 
#define  E_OR 130 
#define  E_SYMBOL 129 
#define  E_UNEQUAL 128 

int expr_contains_symbol(struct expr *dep, struct symbol *sym)
{
	if (!dep)
		return 0;

	switch (dep->type) {
	case E_AND:
	case E_OR:
		return expr_contains_symbol(dep->left.expr, sym) ||
		       expr_contains_symbol(dep->right.expr, sym);
	case E_SYMBOL:
		return dep->left.sym == sym;
	case E_EQUAL:
	case E_GEQ:
	case E_GTH:
	case E_LEQ:
	case E_LTH:
	case E_UNEQUAL:
		return dep->left.sym == sym ||
		       dep->right.sym == sym;
	case E_NOT:
		return expr_contains_symbol(dep->left.expr, sym);
	default:
		;
	}
	return 0;
}