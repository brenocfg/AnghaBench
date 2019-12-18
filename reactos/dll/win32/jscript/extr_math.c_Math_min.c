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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  unsigned int DWORD ;
typedef  scalar_t__ DOUBLE ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ INFINITY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ isnan (scalar_t__) ; 
 int /*<<< orphan*/  jsval_number (scalar_t__) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static HRESULT Math_min(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    DOUBLE min, d;
    DWORD i;
    HRESULT hres;

    TRACE("\n");

    if(!argc) {
        if(r)
            *r = jsval_number(INFINITY);
        return S_OK;
    }

    hres = to_number(ctx, argv[0], &min);
    if(FAILED(hres))
        return hres;

    for(i=1; i < argc; i++) {
        hres = to_number(ctx, argv[i], &d);
        if(FAILED(hres))
            return hres;

        if(d < min || isnan(d))
            min = d;
    }

    if(r)
        *r = jsval_number(min);
    return S_OK;
}