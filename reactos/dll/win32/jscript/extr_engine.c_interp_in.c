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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_OBJECT_EXPECTED ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ disp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 scalar_t__ stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT interp_in(script_ctx_t *ctx)
{
    const WCHAR *str;
    jsstr_t *jsstr;
    jsval_t obj, v;
    DISPID id = 0;
    BOOL ret;
    HRESULT hres;

    TRACE("\n");

    obj = stack_pop(ctx);
    if(!is_object_instance(obj) || !get_object(obj)) {
        jsval_release(obj);
        return throw_type_error(ctx, JS_E_OBJECT_EXPECTED, NULL);
    }

    v = stack_pop(ctx);
    hres = to_flat_string(ctx, v, &jsstr, &str);
    jsval_release(v);
    if(FAILED(hres)) {
        IDispatch_Release(get_object(obj));
        return hres;
    }

    hres = disp_get_id(ctx, get_object(obj), str, NULL, 0, &id);
    IDispatch_Release(get_object(obj));
    jsstr_release(jsstr);
    if(SUCCEEDED(hres))
        ret = TRUE;
    else if(hres == DISP_E_UNKNOWNNAME)
        ret = FALSE;
    else
        return hres;

    return stack_push(ctx, jsval_bool(ret));
}