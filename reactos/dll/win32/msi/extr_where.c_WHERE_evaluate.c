#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  expr; int /*<<< orphan*/  uval; int /*<<< orphan*/  column; } ;
struct expr {int type; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  rec_index; } ;
typedef  TYPE_2__ MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
#define  EXPR_COL_NUMBER 134 
#define  EXPR_COL_NUMBER32 133 
#define  EXPR_COMPLEX 132 
#define  EXPR_STRCMP 131 
#define  EXPR_UNARY 130 
#define  EXPR_UVAL 129 
#define  EXPR_WILDCARD 128 
 int /*<<< orphan*/  INT_evaluate_binary (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_evaluate_unary (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_RecordGetInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRCMP_Evaluate (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expr_fetch_value (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT WHERE_evaluate( MSIWHEREVIEW *wv, const UINT rows[],
                            struct expr *cond, INT *val, MSIRECORD *record )
{
    UINT r, tval;

    if( !cond )
    {
        *val = TRUE;
        return ERROR_SUCCESS;
    }

    switch( cond->type )
    {
    case EXPR_COL_NUMBER:
        r = expr_fetch_value(&cond->u.column, rows, &tval);
        if( r != ERROR_SUCCESS )
            return r;
        *val = tval - 0x8000;
        return ERROR_SUCCESS;

    case EXPR_COL_NUMBER32:
        r = expr_fetch_value(&cond->u.column, rows, &tval);
        if( r != ERROR_SUCCESS )
            return r;
        *val = tval - 0x80000000;
        return r;

    case EXPR_UVAL:
        *val = cond->u.uval;
        return ERROR_SUCCESS;

    case EXPR_COMPLEX:
        return INT_evaluate_binary(wv, rows, &cond->u.expr, val, record);

    case EXPR_UNARY:
        return INT_evaluate_unary( wv, rows, &cond->u.expr, val, record );

    case EXPR_STRCMP:
        return STRCMP_Evaluate( wv, rows, &cond->u.expr, val, record );

    case EXPR_WILDCARD:
        *val = MSI_RecordGetInteger( record, ++wv->rec_index );
        return ERROR_SUCCESS;

    default:
        ERR("Invalid expression type\n");
        return ERROR_FUNCTION_FAILED;
    }

    return ERROR_SUCCESS;
}