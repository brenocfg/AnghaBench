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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  dispex_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int FALSE ; 
 scalar_t__ IDispatchEx_DeleteMemberByName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatch_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ delete_prop (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fdexNameCaseSensitive ; 
 scalar_t__ find_prop_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_grfdex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_hash (int /*<<< orphan*/  const*) ; 

HRESULT disp_delete_name(script_ctx_t *ctx, IDispatch *disp, jsstr_t *name, BOOL *ret)
{
    IDispatchEx *dispex;
    jsdisp_t *jsdisp;
    BSTR bstr;
    HRESULT hres;

    jsdisp = iface_to_jsdisp(disp);
    if(jsdisp) {
        dispex_prop_t *prop;
        const WCHAR *ptr;

        ptr = jsstr_flatten(name);
        if(!ptr) {
            jsdisp_release(jsdisp);
            return E_OUTOFMEMORY;
        }

        hres = find_prop_name(jsdisp, string_hash(ptr), ptr, &prop);
        if(prop) {
            hres = delete_prop(prop, ret);
        }else {
            *ret = TRUE;
            hres = S_OK;
        }

        jsdisp_release(jsdisp);
        return hres;
    }

    bstr = SysAllocStringLen(NULL, jsstr_length(name));
    if(!bstr)
        return E_OUTOFMEMORY;
    jsstr_flush(name, bstr);

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    if(SUCCEEDED(hres)) {
        hres = IDispatchEx_DeleteMemberByName(dispex, bstr, make_grfdex(ctx, fdexNameCaseSensitive));
        if(SUCCEEDED(hres))
            *ret = hres == S_OK;
        IDispatchEx_Release(dispex);
    }else {
        DISPID id;

        hres = IDispatch_GetIDsOfNames(disp, &IID_NULL, &bstr, 1, 0, &id);
        if(SUCCEEDED(hres)) {
            /* Property exists and we can't delete it from pure IDispatch interface, so return false. */
            *ret = FALSE;
        }else if(hres == DISP_E_UNKNOWNNAME) {
            /* Property doesn't exist, so nothing to delete */
            *ret = TRUE;
            hres = S_OK;
        }
    }

    SysFreeString(bstr);
    return hres;
}