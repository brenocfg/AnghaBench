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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int /*<<< orphan*/  safearray; } ;
typedef  TYPE_1__ VBArrayInstance ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_VBARRAY_EXPECTED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayAccessData (int /*<<< orphan*/ ,void**) ; 
 int SafeArrayGetDim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SafeArrayGetLBound (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  SafeArrayGetUBound (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  SafeArrayUnaccessData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  create_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  variant_to_jsval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* vbarray_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT VBArray_toArray(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    VBArrayInstance *vbarray;
    jsdisp_t *array;
    jsval_t val;
    VARIANT *v;
    int i, size = 1, ubound, lbound;
    HRESULT hres;

    TRACE("\n");

    vbarray = vbarray_this(vthis);
    if(!vbarray)
        return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

    for(i=1; i<=SafeArrayGetDim(vbarray->safearray); i++) {
        SafeArrayGetLBound(vbarray->safearray, i, &lbound);
        SafeArrayGetUBound(vbarray->safearray, i, &ubound);
        size *= ubound-lbound+1;
    }

    hres = SafeArrayAccessData(vbarray->safearray, (void**)&v);
    if(FAILED(hres))
        return hres;

    hres = create_array(ctx, 0, &array);
    if(FAILED(hres)) {
        SafeArrayUnaccessData(vbarray->safearray);
        return hres;
    }

    for(i=0; i<size; i++) {
        hres = variant_to_jsval(v, &val);
        if(SUCCEEDED(hres)) {
            hres = jsdisp_propput_idx(array, i, val);
            jsval_release(val);
        }
        if(FAILED(hres)) {
            SafeArrayUnaccessData(vbarray->safearray);
            jsdisp_release(array);
            return hres;
        }
        v++;
    }

    SafeArrayUnaccessData(vbarray->safearray);

    if(r)
        *r = jsval_obj(array);
    else
        jsdisp_release(array);
    return S_OK;
}