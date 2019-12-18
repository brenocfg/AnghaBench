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
struct table {int dummy; } ;
struct complex_expr {int op; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ LONGLONG ;
typedef  scalar_t__ INT_PTR ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  OP_AND 135 
#define  OP_EQ 134 
#define  OP_GE 133 
#define  OP_GT 132 
#define  OP_LE 131 
#define  OP_LT 130 
#define  OP_NE 129 
#define  OP_OR 128 
 scalar_t__ S_OK ; 
 scalar_t__ WBEM_E_INVALID_QUERY ; 
 scalar_t__ eval_boolcmp (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ eval_cond (struct table const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ eval_strcmp (int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/ * format_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ is_boolcmp (struct complex_expr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_int (int /*<<< orphan*/ ) ; 
 scalar_t__ is_strcmp (struct complex_expr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT eval_binary( const struct table *table, UINT row, const struct complex_expr *expr,
                            LONGLONG *val, UINT *type )
{
    HRESULT lret, rret;
    LONGLONG lval, rval;
    UINT ltype, rtype;

    lret = eval_cond( table, row, expr->left, &lval, &ltype );
    rret = eval_cond( table, row, expr->right, &rval, &rtype );
    if (lret != S_OK || rret != S_OK) return WBEM_E_INVALID_QUERY;

    *type = resolve_type( ltype, rtype );

    if (is_boolcmp( expr, ltype, rtype ))
        return eval_boolcmp( expr->op, lval, rval, ltype, rtype, val );

    if (is_strcmp( expr, ltype, rtype ))
    {
        const WCHAR *lstr, *rstr;
        WCHAR lbuf[21], rbuf[21];

        if (is_int( ltype )) lstr = format_int( lbuf, ltype, lval );
        else lstr = (const WCHAR *)(INT_PTR)lval;

        if (is_int( rtype )) rstr = format_int( rbuf, rtype, rval );
        else rstr = (const WCHAR *)(INT_PTR)rval;

        return eval_strcmp( expr->op, lstr, rstr, val );
    }
    switch (expr->op)
    {
    case OP_EQ:
        *val = (lval == rval);
        break;
    case OP_AND:
        *val = (lval && rval);
        break;
    case OP_OR:
        *val = (lval || rval);
        break;
    case OP_GT:
        *val = (lval > rval);
        break;
    case OP_LT:
        *val = (lval < rval);
        break;
    case OP_LE:
        *val = (lval <= rval);
        break;
    case OP_GE:
        *val = (lval >= rval);
        break;
    case OP_NE:
        *val = (lval != rval);
        break;
    default:
        ERR("unhandled operator %u\n", expr->op);
        return WBEM_E_INVALID_QUERY;
    }
    return S_OK;
}