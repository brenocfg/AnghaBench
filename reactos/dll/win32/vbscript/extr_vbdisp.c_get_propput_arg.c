#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {unsigned int cNamedArgs; scalar_t__* rgdispidNamedArgs; int /*<<< orphan*/ * rgvarg; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DISPPARAMS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DISPATCH_PROPERTYPUT ; 
 int DISPATCH_PROPERTYPUTREF ; 
 scalar_t__ DISPID_PROPERTYPUT ; 
 int /*<<< orphan*/  DISP_E_EXCEPTION ; 
 int /*<<< orphan*/  DISP_E_PARAMNOTOPTIONAL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int VT_BYREF ; 
 int VT_DISPATCH ; 
 int VT_VARIANT ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * V_VARIANTREF (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_disp_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT get_propput_arg(script_ctx_t *ctx, const DISPPARAMS *dp, WORD flags, VARIANT *v, BOOL *is_owned)
{
    unsigned i;

    for(i=0; i < dp->cNamedArgs; i++) {
        if(dp->rgdispidNamedArgs[i] == DISPID_PROPERTYPUT)
            break;
    }
    if(i == dp->cNamedArgs) {
        WARN("no value to set\n");
        return DISP_E_PARAMNOTOPTIONAL;
    }

    *v = dp->rgvarg[i];
    if(V_VT(v) == (VT_VARIANT|VT_BYREF))
        *v = *V_VARIANTREF(v);
    *is_owned = FALSE;

    if(V_VT(v) == VT_DISPATCH) {
        if(!(flags & DISPATCH_PROPERTYPUTREF)) {
            HRESULT hres;

            hres = get_disp_value(ctx, V_DISPATCH(v), v);
            if(FAILED(hres))
                return hres;

            *is_owned = TRUE;
        }
    }else if(!(flags & DISPATCH_PROPERTYPUT)) {
        WARN("%s can't be assigned without DISPATCH_PROPERTYPUT flag\n", debugstr_variant(v));
        return DISP_E_EXCEPTION;
    }

    return S_OK;
}