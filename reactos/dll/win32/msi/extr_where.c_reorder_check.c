#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct expr* left; struct expr* right; } ;
struct TYPE_5__ {int /*<<< orphan*/ * table; } ;
struct TYPE_6__ {TYPE_1__ parsed; } ;
struct TYPE_8__ {TYPE_3__ expr; TYPE_2__ column; } ;
struct expr {int type; TYPE_4__ u; } ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  JOINTABLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CONST_EXPR ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  EXPR_COL_NUMBER 136 
#define  EXPR_COL_NUMBER32 135 
#define  EXPR_COL_NUMBER_STRING 134 
#define  EXPR_COMPLEX 133 
#define  EXPR_STRCMP 132 
#define  EXPR_SVAL 131 
#define  EXPR_UNARY 130 
#define  EXPR_UVAL 129 
#define  EXPR_WILDCARD 128 
 int JOIN_TO_CONST_EXPR ; 
 int /*<<< orphan*/  add_to_array (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_array (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT reorder_check( const struct expr *expr, JOINTABLE **ordered_tables,
                           BOOL process_joins, JOINTABLE **lastused )
{
    UINT res = 0;

    switch (expr->type)
    {
        case EXPR_WILDCARD:
        case EXPR_SVAL:
        case EXPR_UVAL:
            return 0;
        case EXPR_COL_NUMBER:
        case EXPR_COL_NUMBER32:
        case EXPR_COL_NUMBER_STRING:
            if (in_array(ordered_tables, expr->u.column.parsed.table))
                return JOIN_TO_CONST_EXPR;
            *lastused = expr->u.column.parsed.table;
            return CONST_EXPR;
        case EXPR_STRCMP:
        case EXPR_COMPLEX:
            res = reorder_check(expr->u.expr.right, ordered_tables, process_joins, lastused);
            /* fall through */
        case EXPR_UNARY:
            res += reorder_check(expr->u.expr.left, ordered_tables, process_joins, lastused);
            if (res == 0)
                return 0;
            if (res == CONST_EXPR)
                add_to_array(ordered_tables, *lastused);
            if (process_joins && res == JOIN_TO_CONST_EXPR + CONST_EXPR)
                add_to_array(ordered_tables, *lastused);
            return res;
        default:
            ERR("Unknown expr type: %i\n", expr->type);
            assert(0);
            return 0x1000000;
    }
}