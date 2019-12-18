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
typedef  int /*<<< orphan*/  exec_ctx_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int VT_BYREF ; 
 int VT_DISPATCH ; 
 int VT_VARIANT ; 
 int /*<<< orphan*/ * V_BYREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stack_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT stack_pop_disp(exec_ctx_t *ctx, IDispatch **ret)
{
    VARIANT *v = stack_pop(ctx);

    if(V_VT(v) == VT_DISPATCH) {
        *ret = V_DISPATCH(v);
        return S_OK;
    }

    if(V_VT(v) != (VT_VARIANT|VT_BYREF)) {
        FIXME("not supported type: %s\n", debugstr_variant(v));
        VariantClear(v);
        return E_FAIL;
    }

    v = V_BYREF(v);
    if(V_VT(v) != VT_DISPATCH) {
        FIXME("not disp %s\n", debugstr_variant(v));
        return E_FAIL;
    }

    if(V_DISPATCH(v))
        IDispatch_AddRef(V_DISPATCH(v));
    *ret = V_DISPATCH(v);
    return S_OK;
}