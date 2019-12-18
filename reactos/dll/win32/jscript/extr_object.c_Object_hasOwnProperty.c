#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  disp; int /*<<< orphan*/  dispex; int /*<<< orphan*/  jsdisp; } ;
struct TYPE_11__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
struct TYPE_12__ {int /*<<< orphan*/  lcid; } ;
typedef  TYPE_3__ script_ctx_t ;
typedef  int /*<<< orphan*/  property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FALSE ; 
 scalar_t__ IDispatchEx_GetDispID (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatch_GetIDsOfNames (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_NULL ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fdexNameCaseSensitive ; 
 scalar_t__ is_dispex (TYPE_2__*) ; 
 scalar_t__ is_jsdisp (TYPE_2__*) ; 
 scalar_t__ jsdisp_get_own_property (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int) ; 
 int /*<<< orphan*/  make_grfdex (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ to_string (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Object_hasOwnProperty(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsstr_t *name;
    DISPID id;
    BSTR bstr;
    HRESULT hres;

    TRACE("\n");

    if(!argc) {
        if(r)
            *r = jsval_bool(FALSE);
        return S_OK;
    }

    hres = to_string(ctx, argv[0], &name);
    if(FAILED(hres))
        return hres;

    if(is_jsdisp(jsthis)) {
        property_desc_t prop_desc;
        const WCHAR *name_str;

        name_str = jsstr_flatten(name);
        if(!name_str) {
            jsstr_release(name);
            return E_OUTOFMEMORY;
        }

        hres = jsdisp_get_own_property(jsthis->u.jsdisp, name_str, TRUE, &prop_desc);
        jsstr_release(name);
        if(FAILED(hres) && hres != DISP_E_UNKNOWNNAME)
            return hres;

        if(r) *r = jsval_bool(hres == S_OK);
        return S_OK;
    }


    bstr = SysAllocStringLen(NULL, jsstr_length(name));
    if(bstr)
        jsstr_flush(name, bstr);
    jsstr_release(name);
    if(!bstr)
        return E_OUTOFMEMORY;

    if(is_dispex(jsthis))
        hres = IDispatchEx_GetDispID(jsthis->u.dispex, bstr, make_grfdex(ctx, fdexNameCaseSensitive), &id);
    else
        hres = IDispatch_GetIDsOfNames(jsthis->u.disp, &IID_NULL, &bstr, 1, ctx->lcid, &id);

    SysFreeString(bstr);
    if(r)
        *r = jsval_bool(SUCCEEDED(hres));
    return S_OK;
}