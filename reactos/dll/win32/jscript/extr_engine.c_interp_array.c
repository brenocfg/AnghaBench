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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ disp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ disp_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 scalar_t__ stack_pop_object (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT interp_array(script_ctx_t *ctx)
{
    jsstr_t *name_str;
    const WCHAR *name;
    jsval_t v, namev;
    IDispatch *obj;
    DISPID id;
    HRESULT hres;

    TRACE("\n");

    namev = stack_pop(ctx);

    hres = stack_pop_object(ctx, &obj);
    if(FAILED(hres)) {
        jsval_release(namev);
        return hres;
    }

    hres = to_flat_string(ctx, namev, &name_str, &name);
    jsval_release(namev);
    if(FAILED(hres)) {
        IDispatch_Release(obj);
        return hres;
    }

    hres = disp_get_id(ctx, obj, name, NULL, 0, &id);
    jsstr_release(name_str);
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