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
struct complex_expr {int op; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ ERROR_CONTINUE ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
#define  OP_AND 135 
#define  OP_EQ 134 
#define  OP_GE 133 
#define  OP_GT 132 
#define  OP_LE 131 
#define  OP_LT 130 
#define  OP_NE 129 
#define  OP_OR 128 
 scalar_t__ TRUE ; 
 scalar_t__ WHERE_evaluate (int /*<<< orphan*/ *,scalar_t__ const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT INT_evaluate_binary( MSIWHEREVIEW *wv, const UINT rows[],
                                const struct complex_expr *expr, INT *val, MSIRECORD *record )
{
    UINT rl, rr;
    INT lval, rval;

    rl = WHERE_evaluate(wv, rows, expr->left, &lval, record);
    if (rl != ERROR_SUCCESS && rl != ERROR_CONTINUE)
        return rl;
    rr = WHERE_evaluate(wv, rows, expr->right, &rval, record);
    if (rr != ERROR_SUCCESS && rr != ERROR_CONTINUE)
        return rr;

    if (rl == ERROR_CONTINUE || rr == ERROR_CONTINUE)
    {
        if (rl == rr)
        {
            *val = TRUE;
            return ERROR_CONTINUE;
        }

        if (expr->op == OP_AND)
        {
            if ((rl == ERROR_CONTINUE && !rval) || (rr == ERROR_CONTINUE && !lval))
            {
                *val = FALSE;
                return ERROR_SUCCESS;
            }
        }
        else if (expr->op == OP_OR)
        {
            if ((rl == ERROR_CONTINUE && rval) || (rr == ERROR_CONTINUE && lval))
            {
                *val = TRUE;
                return ERROR_SUCCESS;
            }
        }

        *val = TRUE;
        return ERROR_CONTINUE;
    }

    switch( expr->op )
    {
    case OP_EQ:
        *val = ( lval == rval );
        break;
    case OP_AND:
        *val = ( lval && rval );
        break;
    case OP_OR:
        *val = ( lval || rval );
        break;
    case OP_GT:
        *val = ( lval > rval );
        break;
    case OP_LT:
        *val = ( lval < rval );
        break;
    case OP_LE:
        *val = ( lval <= rval );
        break;
    case OP_GE:
        *val = ( lval >= rval );
        break;
    case OP_NE:
        *val = ( lval != rval );
        break;
    default:
        ERR("Unknown operator %d\n", expr->op );
        return ERROR_FUNCTION_FAILED;
    }

    return ERROR_SUCCESS;
}