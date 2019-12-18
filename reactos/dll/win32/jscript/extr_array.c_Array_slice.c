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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  create_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_get_idx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Array_slice(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv, jsval_t *r)
{
    jsdisp_t *arr, *jsthis;
    DOUBLE range;
    DWORD length, start, end, idx;
    HRESULT hres;

    TRACE("\n");

    hres = get_length(ctx, vthis, &jsthis, &length);
    if(FAILED(hres))
        return hres;

    if(argc) {
        hres = to_number(ctx, argv[0], &range);
        if(FAILED(hres))
            return hres;

        range = floor(range);
        if(-range>length || isnan(range)) start = 0;
        else if(range < 0) start = range+length;
        else if(range <= length) start = range;
        else start = length;
    }
    else start = 0;

    if(argc > 1) {
        hres = to_number(ctx, argv[1], &range);
        if(FAILED(hres))
            return hres;

        range = floor(range);
        if(-range>length) end = 0;
        else if(range < 0) end = range+length;
        else if(range <= length) end = range;
        else end = length;
    }
    else end = length;

    hres = create_array(ctx, (end>start)?end-start:0, &arr);
    if(FAILED(hres))
        return hres;

    for(idx=start; idx<end; idx++) {
        jsval_t v;

        hres = jsdisp_get_idx(jsthis, idx, &v);
        if(hres == DISP_E_UNKNOWNNAME)
            continue;

        if(SUCCEEDED(hres)) {
            hres = jsdisp_propput_idx(arr, idx-start, v);
            jsval_release(v);
        }

        if(FAILED(hres)) {
            jsdisp_release(arr);
            return hres;
        }
    }

    if(r)
        *r = jsval_obj(arr);
    else
        jsdisp_release(arr);

    return S_OK;
}