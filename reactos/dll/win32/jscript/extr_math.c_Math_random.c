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
typedef  int /*<<< orphan*/  x ;
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_UNEXPECTED ; 
 int /*<<< orphan*/  RtlGenRandom (scalar_t__*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  jsval_number (double) ; 

__attribute__((used)) static HRESULT Math_random(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    UINT x;

    TRACE("\n");

    if(!RtlGenRandom(&x, sizeof(x)))
        return E_UNEXPECTED;

    if(r)
        *r = jsval_number((double)x/(double)UINT_MAX);
    return S_OK;
}