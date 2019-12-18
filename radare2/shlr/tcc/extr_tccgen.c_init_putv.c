#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int r; } ;
struct TYPE_5__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ CType ;

/* Variables and functions */
#define  EXPR_ANY 130 
#define  EXPR_CONST 129 
#define  EXPR_VAL 128 
 int /*<<< orphan*/  TCC_ERR (char*) ; 
 int VT_CONST ; 
 int /*<<< orphan*/  VT_CONSTANT ; 
 int VT_LOCAL ; 
 int VT_LVAL ; 
 int VT_VALMASK ; 
 int /*<<< orphan*/  expr_const1 () ; 
 int /*<<< orphan*/  expr_eq () ; 
 int global_expr ; 
 int /*<<< orphan*/  vpushll (long long) ; 
 int /*<<< orphan*/  vset (TYPE_1__*,int,unsigned long) ; 
 int /*<<< orphan*/  vswap () ; 
 TYPE_2__* vtop ; 

__attribute__((used)) static void init_putv(CType *type, unsigned long c, long long v, int expr_type) {
	int saved_global_expr;
	CType dtype;

	switch (expr_type) {
	case EXPR_VAL:
		vpushll (v);
		break;
	case EXPR_CONST:
		/* compound literals must be allocated globally in this case */
		saved_global_expr = global_expr;
		global_expr = 1;
		expr_const1 ();
		global_expr = saved_global_expr;
		/* NOTE: symbols are accepted */
		if ((vtop->r & (VT_VALMASK | VT_LVAL)) != VT_CONST) {
			TCC_ERR ("initializer element is not constant");
		}
		break;
	case EXPR_ANY:
		expr_eq ();
		break;
	}

	dtype = *type;
	dtype.t &= ~VT_CONSTANT;/* need to do that to avoid false warning */

	vset (&dtype, VT_LOCAL | VT_LVAL, c);
	vswap ();
}