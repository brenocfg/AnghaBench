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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*) ; 
 int /*<<< orphan*/  jsdisp_get_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_strict_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 unsigned int max (double,int /*<<< orphan*/ ) ; 
 unsigned int min (double,unsigned int) ; 
 int /*<<< orphan*/  to_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT Array_indexOf(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *jsthis;
    unsigned length, i, from = 0;
    jsval_t search, value;
    BOOL eq;
    HRESULT hres;

    TRACE("\n");

    hres = get_length(ctx, vthis, &jsthis, &length);
    if(FAILED(hres))
        return hres;
    if(!length) {
        if(r) *r = jsval_number(-1);
        return S_OK;
    }

    search = argc ? argv[0] : jsval_undefined();

    if(argc > 1) {
        double from_arg;

        hres = to_integer(ctx, argv[1], &from_arg);
        if(FAILED(hres))
            return hres;

        if(from_arg >= 0)
            from = min(from_arg, length);
        else
            from = max(from_arg + length, 0);
    }

    for(i = from; i < length; i++) {
        hres = jsdisp_get_idx(jsthis, i, &value);
        if(hres == DISP_E_UNKNOWNNAME)
            continue;
        if(FAILED(hres))
            return hres;

        hres = jsval_strict_equal(value, search, &eq);
        jsval_release(value);
        if(FAILED(hres))
            return hres;
        if(eq) {
            if(r) *r = jsval_number(i);
            return S_OK;
        }
    }

    if(r) *r = jsval_number(-1);
    return S_OK;
}