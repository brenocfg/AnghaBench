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
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  jsdisp_addref (int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_delete_idx (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jsdisp_get_idx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_propput_idx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Array_reverse(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *jsthis;
    DWORD length, k, l;
    jsval_t v1, v2;
    HRESULT hres1, hres2;

    TRACE("\n");

    hres1 = get_length(ctx, vthis, &jsthis, &length);
    if(FAILED(hres1))
        return hres1;

    for(k=0; k<length/2; k++) {
        l = length-k-1;

        hres1 = jsdisp_get_idx(jsthis, k, &v1);
        if(FAILED(hres1) && hres1!=DISP_E_UNKNOWNNAME)
            return hres1;

        hres2 = jsdisp_get_idx(jsthis, l, &v2);
        if(FAILED(hres2) && hres2!=DISP_E_UNKNOWNNAME) {
            jsval_release(v1);
            return hres2;
        }

        if(hres1 == DISP_E_UNKNOWNNAME)
            hres1 = jsdisp_delete_idx(jsthis, l);
        else
            hres1 = jsdisp_propput_idx(jsthis, l, v1);

        if(FAILED(hres1)) {
            jsval_release(v1);
            jsval_release(v2);
            return hres1;
        }

        if(hres2 == DISP_E_UNKNOWNNAME)
            hres2 = jsdisp_delete_idx(jsthis, k);
        else
            hres2 = jsdisp_propput_idx(jsthis, k, v2);

        if(FAILED(hres2)) {
            jsval_release(v2);
            return hres2;
        }
    }

    if(r)
        *r = jsval_obj(jsdisp_addref(jsthis));
    return S_OK;
}