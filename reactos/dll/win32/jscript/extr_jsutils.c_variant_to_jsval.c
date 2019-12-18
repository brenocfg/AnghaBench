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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysStringLen (int /*<<< orphan*/ ) ; 
#define  VT_BOOL 143 
#define  VT_BSTR 142 
 int VT_BYREF ; 
#define  VT_DISPATCH 141 
#define  VT_EMPTY 140 
#define  VT_I1 139 
#define  VT_I2 138 
#define  VT_I4 137 
#define  VT_INT 136 
#define  VT_NULL 135 
#define  VT_R4 134 
#define  VT_R8 133 
#define  VT_UI1 132 
#define  VT_UI2 131 
#define  VT_UI4 130 
#define  VT_UI8 129 
#define  VT_UNKNOWN 128 
 int VT_VARIANT ; 
 int /*<<< orphan*/  V_BOOL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_I1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_I2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_INT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_R4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_R8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UI1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UI2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UI4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UI8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UNKNOWN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * V_VARIANTREF (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_null_bstr () ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  jsval_variant (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT variant_to_jsval(VARIANT *var, jsval_t *r)
{
    if(V_VT(var) == (VT_VARIANT|VT_BYREF))
        var = V_VARIANTREF(var);

    switch(V_VT(var)) {
    case VT_EMPTY:
        *r = jsval_undefined();
        return S_OK;
    case VT_NULL:
        *r = jsval_null();
        return S_OK;
    case VT_BOOL:
        *r = jsval_bool(V_BOOL(var));
        return S_OK;
    case VT_I4:
        *r = jsval_number(V_I4(var));
        return S_OK;
    case VT_R8:
        *r = jsval_number(V_R8(var));
        return S_OK;
    case VT_BSTR: {
        jsstr_t *str;

        if(V_BSTR(var)) {
            str = jsstr_alloc_len(V_BSTR(var), SysStringLen(V_BSTR(var)));
            if(!str)
                return E_OUTOFMEMORY;
        }else {
            str = jsstr_null_bstr();
        }

        *r = jsval_string(str);
        return S_OK;
    }
    case VT_DISPATCH: {
        if(V_DISPATCH(var))
            IDispatch_AddRef(V_DISPATCH(var));
        *r = jsval_disp(V_DISPATCH(var));
        return S_OK;
    }
    case VT_I1:
        *r = jsval_number(V_I1(var));
        return S_OK;
    case VT_UI1:
        *r = jsval_number(V_UI1(var));
        return S_OK;
    case VT_I2:
        *r = jsval_number(V_I2(var));
        return S_OK;
    case VT_UI2:
        *r = jsval_number(V_UI2(var));
        return S_OK;
    case VT_INT:
        *r = jsval_number(V_INT(var));
        return S_OK;
    case VT_UI4:
        *r = jsval_number(V_UI4(var));
        return S_OK;
    case VT_UI8:
        /*
         * Native doesn't support VT_UI8 here, but it's needed for IE9+ APIs
         * (native IE9 doesn't use jscript.dll for JavaScript).
         */
        *r = jsval_number(V_UI8(var));
        return S_OK;
    case VT_R4:
        *r = jsval_number(V_R4(var));
        return S_OK;
    case VT_UNKNOWN:
        if(V_UNKNOWN(var)) {
            IDispatch *disp;
            HRESULT hres;

            hres = IUnknown_QueryInterface(V_UNKNOWN(var), &IID_IDispatch, (void**)&disp);
            if(SUCCEEDED(hres)) {
                *r = jsval_disp(disp);
                return S_OK;
            }
        }else {
            *r = jsval_disp(NULL);
            return S_OK;
        }
        /* fall through */
    default:
        return jsval_variant(r, var);
    }
}