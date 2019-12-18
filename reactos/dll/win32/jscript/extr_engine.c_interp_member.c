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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ disp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ disp_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_op_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 scalar_t__ stack_pop_object (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_member(script_ctx_t *ctx)
{
    const BSTR arg = get_op_bstr(ctx, 0);
    IDispatch *obj;
    jsval_t v;
    DISPID id;
    HRESULT hres;

    TRACE("\n");

    hres = stack_pop_object(ctx, &obj);
    if(FAILED(hres))
        return hres;

    hres = disp_get_id(ctx, obj, arg, arg, 0, &id);
    if(SUCCEEDED(hres)) {
        hres = disp_propget(ctx, obj, id, &v);
    }else if(hres == DISP_E_UNKNOWNNAME) {
        v = jsval_undefined();
        hres = S_OK;
    }
    IDispatch_Release(obj);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, v);
}