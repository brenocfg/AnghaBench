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
struct TYPE_3__ {struct expr* left; int /*<<< orphan*/  op; struct expr* right; } ;
struct TYPE_4__ {int /*<<< orphan*/  ival; int /*<<< orphan*/  uval; TYPE_1__ expr; int /*<<< orphan*/  column; } ;
struct expr {int type; TYPE_2__ u; } ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIWHEREVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
#define  EXPR_COLUMN 135 
 int EXPR_COL_NUMBER ; 
 int EXPR_COL_NUMBER32 ; 
 int EXPR_COL_NUMBER_STRING ; 
#define  EXPR_COMPLEX 134 
#define  EXPR_IVAL 133 
 int EXPR_STRCMP ; 
#define  EXPR_SVAL 132 
#define  EXPR_UNARY 131 
 int EXPR_UVAL ; 
#define  EXPR_WILDCARD 130 
 int FALSE ; 
 int MSITYPE_STRING ; 
#define  OP_EQ 129 
#define  OP_NE 128 
 int TRUE ; 
 int parse_column (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static UINT WHERE_VerifyCondition( MSIWHEREVIEW *wv, struct expr *cond,
                                   UINT *valid )
{
    UINT r;

    switch( cond->type )
    {
    case EXPR_COLUMN:
    {
        UINT type;

        *valid = FALSE;

        r = parse_column(wv, &cond->u.column, &type);
        if (r != ERROR_SUCCESS)
            break;

        if (type&MSITYPE_STRING)
            cond->type = EXPR_COL_NUMBER_STRING;
        else if ((type&0xff) == 4)
            cond->type = EXPR_COL_NUMBER32;
        else
            cond->type = EXPR_COL_NUMBER;

        *valid = TRUE;
        break;
    }
    case EXPR_COMPLEX:
        r = WHERE_VerifyCondition( wv, cond->u.expr.left, valid );
        if( r != ERROR_SUCCESS )
            return r;
        if( !*valid )
            return ERROR_SUCCESS;
        r = WHERE_VerifyCondition( wv, cond->u.expr.right, valid );
        if( r != ERROR_SUCCESS )
            return r;

        /* check the type of the comparison */
        if( ( cond->u.expr.left->type == EXPR_SVAL ) ||
            ( cond->u.expr.left->type == EXPR_COL_NUMBER_STRING ) ||
            ( cond->u.expr.right->type == EXPR_SVAL ) ||
            ( cond->u.expr.right->type == EXPR_COL_NUMBER_STRING ) )
        {
            switch( cond->u.expr.op )
            {
            case OP_EQ:
            case OP_NE:
                break;
            default:
                *valid = FALSE;
                return ERROR_INVALID_PARAMETER;
            }

            /* FIXME: check we're comparing a string to a column */

            cond->type = EXPR_STRCMP;
        }

        break;
    case EXPR_UNARY:
        if ( cond->u.expr.left->type != EXPR_COLUMN )
        {
            *valid = FALSE;
            return ERROR_INVALID_PARAMETER;
        }
        r = WHERE_VerifyCondition( wv, cond->u.expr.left, valid );
        if( r != ERROR_SUCCESS )
            return r;
        break;
    case EXPR_IVAL:
        *valid = 1;
        cond->type = EXPR_UVAL;
        cond->u.uval = cond->u.ival;
        break;
    case EXPR_WILDCARD:
        *valid = 1;
        break;
    case EXPR_SVAL:
        *valid = 1;
        break;
    default:
        ERR("Invalid expression type\n");
        *valid = 0;
        break;
    }

    return ERROR_SUCCESS;
}