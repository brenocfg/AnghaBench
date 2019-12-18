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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 double floor (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

HRESULT to_integer(script_ctx_t *ctx, jsval_t v, double *ret)
{
    double n;
    HRESULT hres;

    hres = to_number(ctx, v, &n);
    if(FAILED(hres))
        return hres;

    if(isnan(n))
        *ret = 0;
    else
        *ret = n >= 0.0 ? floor(n) : -floor(-n);
    return S_OK;
}