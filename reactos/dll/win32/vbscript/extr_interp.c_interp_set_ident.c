#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* instr; } ;
typedef  TYPE_4__ exec_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/  bstr; } ;
struct TYPE_11__ {unsigned int uint; } ;
struct TYPE_12__ {TYPE_1__ arg1; TYPE_2__ arg2; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPPARAMS ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYPUTREF ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assign_ident (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stack_assume_disp (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_popn (TYPE_4__*,int) ; 
 int /*<<< orphan*/  vbstack_to_dp (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_set_ident(exec_ctx_t *ctx)
{
    const BSTR arg = ctx->instr->arg1.bstr;
    const unsigned arg_cnt = ctx->instr->arg2.uint;
    DISPPARAMS dp;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(arg));

    if(arg_cnt) {
        FIXME("arguments not supported\n");
        return E_NOTIMPL;
    }

    hres = stack_assume_disp(ctx, 0, NULL);
    if(FAILED(hres))
        return hres;

    vbstack_to_dp(ctx, 0, TRUE, &dp);
    hres = assign_ident(ctx, ctx->instr->arg1.bstr, DISPATCH_PROPERTYPUTREF, &dp);
    if(FAILED(hres))
        return hres;

    stack_popn(ctx, 1);
    return S_OK;
}