#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ei; } ;
struct TYPE_11__ {TYPE_2__ ei; int /*<<< orphan*/  lcid; TYPE_1__* jscaller; } ;
typedef  TYPE_3__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  dispex_prop_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_12__ {int member_2; int member_3; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  IServiceProvider_iface; } ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_4__ DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYPUT ; 
 int /*<<< orphan*/  DISPATCH_PROPERTYPUTREF ; 
 int /*<<< orphan*/  DISPID_PROPERTYPUT ; 
 int /*<<< orphan*/  DISP_E_MEMBERNOTFOUND ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_InvokeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_ei (TYPE_3__*) ; 
 int /*<<< orphan*/ * get_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_to_variant (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prop_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT disp_propput(script_ctx_t *ctx, IDispatch *disp, DISPID id, jsval_t val)
{
    jsdisp_t *jsdisp;
    HRESULT hres;

    jsdisp = iface_to_jsdisp(disp);
    if(jsdisp) {
        dispex_prop_t *prop;

        prop = get_prop(jsdisp, id);
        if(prop)
            hres = prop_put(jsdisp, prop, val);
        else
            hres = DISP_E_MEMBERNOTFOUND;

        jsdisp_release(jsdisp);
    }else {
        DISPID dispid = DISPID_PROPERTYPUT;
        DWORD flags = DISPATCH_PROPERTYPUT;
        VARIANT var;
        DISPPARAMS dp  = {&var, &dispid, 1, 1};
        IDispatchEx *dispex;

        hres = jsval_to_variant(val, &var);
        if(FAILED(hres))
            return hres;

        if(V_VT(&var) == VT_DISPATCH)
            flags |= DISPATCH_PROPERTYPUTREF;

        clear_ei(ctx);
        hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
        if(SUCCEEDED(hres)) {
            hres = IDispatchEx_InvokeEx(dispex, id, ctx->lcid, flags, &dp, NULL, &ctx->ei.ei,
                    &ctx->jscaller->IServiceProvider_iface);
            IDispatchEx_Release(dispex);
        }else {
            ULONG err = 0;

            TRACE("using IDispatch\n");
            hres = IDispatch_Invoke(disp, id, &IID_NULL, ctx->lcid, flags, &dp, NULL, &ctx->ei.ei, &err);
        }

        VariantClear(&var);
    }

    return hres;
}