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
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int LONGLONG ;
typedef  scalar_t__ INT_PTR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ CIM_STRING ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
#define  OP_EQ 129 
#define  OP_NE 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WBEM_E_INVALID_QUERY ; 
 int /*<<< orphan*/  strcmpiW (char const*,char const*) ; 

__attribute__((used)) static HRESULT eval_boolcmp( UINT op, LONGLONG lval, LONGLONG rval, UINT ltype, UINT rtype, LONGLONG *val )
{
    static const WCHAR trueW[] = {'T','r','u','e',0};

    if (ltype == CIM_STRING) lval = !strcmpiW( (const WCHAR *)(INT_PTR)lval, trueW ) ? -1 : 0;
    else if (rtype == CIM_STRING) rval = !strcmpiW( (const WCHAR *)(INT_PTR)rval, trueW ) ? -1 : 0;

    switch (op)
    {
    case OP_EQ:
        *val = (lval == rval);
        break;
    case OP_NE:
        *val = (lval != rval);
        break;
    default:
        ERR("unhandled operator %u\n", op);
        return WBEM_E_INVALID_QUERY;
    }
    return S_OK;
}