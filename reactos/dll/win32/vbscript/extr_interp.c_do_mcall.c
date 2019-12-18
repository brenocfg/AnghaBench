#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  script; TYPE_3__* instr; } ;
typedef  TYPE_4__ exec_ctx_t ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_9__ {unsigned int uint; } ;
struct TYPE_10__ {int /*<<< orphan*/  bstr; } ;
struct TYPE_11__ {TYPE_1__ arg2; TYPE_2__ arg1; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VBDISP_CALLGET ; 
 int /*<<< orphan*/  disp_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_pop_disp (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stack_popn (TYPE_4__*,unsigned int const) ; 
 int /*<<< orphan*/  vbstack_to_dp (TYPE_4__*,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT do_mcall(exec_ctx_t *ctx, VARIANT *res)
{
    const BSTR identifier = ctx->instr->arg1.bstr;
    const unsigned arg_cnt = ctx->instr->arg2.uint;
    IDispatch *obj;
    DISPPARAMS dp;
    DISPID id;
    HRESULT hres;

    hres = stack_pop_disp(ctx, &obj);
    if(FAILED(hres))
        return hres;

    if(!obj) {
        FIXME("NULL obj\n");
        return E_FAIL;
    }

    vbstack_to_dp(ctx, arg_cnt, FALSE, &dp);

    hres = disp_get_id(obj, identifier, VBDISP_CALLGET, FALSE, &id);
    if(SUCCEEDED(hres))
        hres = disp_call(ctx->script, obj, id, &dp, res);
    IDispatch_Release(obj);
    if(FAILED(hres))
        return hres;

    stack_popn(ctx, arg_cnt);
    return S_OK;
}