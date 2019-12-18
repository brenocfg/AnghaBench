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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_5__ {int /*<<< orphan*/  hres; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ exprval_t ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_GetMemberName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDispatchEx_GetNextDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysStringLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprval_propput (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdexEnumDefault ; 
 int /*<<< orphan*/  get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_number (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_abs (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  jmp_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_popn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_topn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stack_topn_exprval (int /*<<< orphan*/ *,int,TYPE_2__*) ; 

__attribute__((used)) static HRESULT interp_forin(script_ctx_t *ctx)
{
    const HRESULT arg = get_op_uint(ctx, 0);
    IDispatch *obj = NULL;
    IDispatchEx *dispex;
    exprval_t prop_ref;
    DISPID id;
    BSTR name = NULL;
    HRESULT hres;

    TRACE("\n");

    assert(is_number(stack_top(ctx)));
    id = get_number(stack_top(ctx));

    if(!stack_topn_exprval(ctx, 1, &prop_ref)) {
        FIXME("invalid ref: %08x\n", prop_ref.u.hres);
        return E_FAIL;
    }

    if(is_object_instance(stack_topn(ctx, 3)))
        obj = get_object(stack_topn(ctx, 3));

    if(obj) {
        hres = IDispatch_QueryInterface(obj, &IID_IDispatchEx, (void**)&dispex);
        if(SUCCEEDED(hres)) {
            hres = IDispatchEx_GetNextDispID(dispex, fdexEnumDefault, id, &id);
            if(hres == S_OK)
                hres = IDispatchEx_GetMemberName(dispex, id, &name);
            IDispatchEx_Release(dispex);
            if(FAILED(hres))
                return hres;
        }else {
            TRACE("No IDispatchEx\n");
        }
    }

    if(name) {
        jsstr_t *str;

        str = jsstr_alloc_len(name, SysStringLen(name));
        SysFreeString(name);
        if(!str)
            return E_OUTOFMEMORY;

        stack_pop(ctx);
        stack_push(ctx, jsval_number(id)); /* safe, just after pop() */

        hres = exprval_propput(ctx, &prop_ref, jsval_string(str));
        jsstr_release(str);
        if(FAILED(hres))
            return hres;

        jmp_next(ctx);
    }else {
        stack_popn(ctx, 4);
        jmp_abs(ctx, arg);
    }
    return S_OK;
}