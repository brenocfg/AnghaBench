#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * sym; struct expr* expr; } ;
struct TYPE_5__ {TYPE_1__* sym; struct expr* expr; } ;
struct expr {int type; TYPE_3__ right; TYPE_2__ left; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  E_AND 131 
#define  E_NOT 130 
#define  E_OR 129 
 int E_SYMBOL ; 
#define  E_UNEQUAL 128 
 int /*<<< orphan*/  S_TRISTATE ; 
 int /*<<< orphan*/  symbol_no ; 

struct expr *expr_trans_bool(struct expr *e)
{
	if (!e)
		return NULL;
	switch (e->type) {
	case E_AND:
	case E_OR:
	case E_NOT:
		e->left.expr = expr_trans_bool(e->left.expr);
		e->right.expr = expr_trans_bool(e->right.expr);
		break;
	case E_UNEQUAL:
		// FOO!=n -> FOO
		if (e->left.sym->type == S_TRISTATE) {
			if (e->right.sym == &symbol_no) {
				e->type = E_SYMBOL;
				e->right.sym = NULL;
			}
		}
		break;
	default:
		;
	}
	return e;
}