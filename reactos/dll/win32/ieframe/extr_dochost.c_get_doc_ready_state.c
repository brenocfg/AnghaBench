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
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_6__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  document; } ;
typedef  int /*<<< orphan*/  READYSTATE ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  TYPE_1__ DocHost ;
typedef  TYPE_2__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  DISPID_READYSTATE ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IDispatch_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_I4 ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 

__attribute__((used)) static HRESULT get_doc_ready_state(DocHost *This, READYSTATE *ret)
{
    DISPPARAMS dp = {NULL,NULL,0,0};
    IDispatch *disp;
    EXCEPINFO ei;
    VARIANT var;
    HRESULT hres;

    hres = IUnknown_QueryInterface(This->document, &IID_IDispatch, (void**)&disp);
    if(FAILED(hres))
        return hres;

    hres = IDispatch_Invoke(disp, DISPID_READYSTATE, &IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET,
            &dp, &var, &ei, NULL);
    IDispatch_Release(disp);
    if(FAILED(hres)) {
        WARN("Invoke(DISPID_READYSTATE failed: %08x\n", hres);
        return hres;
    }

    if(V_VT(&var) != VT_I4) {
        WARN("V_VT(var) = %d\n", V_VT(&var));
        VariantClear(&var);
        return E_FAIL;
    }

    *ret = V_I4(&var);
    return S_OK;
}