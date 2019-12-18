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
struct TYPE_9__ {unsigned int uint; } ;
struct TYPE_10__ {int /*<<< orphan*/  bstr; } ;
struct TYPE_11__ {TYPE_1__ arg2; TYPE_2__ arg1; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYPUT ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VBDISP_LET ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disp_propput (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_assume_disp (TYPE_4__*,unsigned int const,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stack_popn (TYPE_4__*,unsigned int const) ; 
 int /*<<< orphan*/  vbstack_to_dp (TYPE_4__*,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_assign_member(exec_ctx_t *ctx)
{
    BSTR identifier = ctx->instr->arg1.bstr;
    const unsigned arg_cnt = ctx->instr->arg2.uint;
    IDispatch *obj;
    DISPPARAMS dp;
    DISPID id;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(identifier));

    hres = stack_assume_disp(ctx, arg_cnt+1, &obj);
    if(FAILED(hres))
        return hres;

    if(!obj) {
        FIXME("NULL obj\n");
        return E_FAIL;
    }

    hres = disp_get_id(obj, identifier, VBDISP_LET, FALSE, &id);
    if(SUCCEEDED(hres)) {
        vbstack_to_dp(ctx, arg_cnt, TRUE, &dp);
        hres = disp_propput(ctx->script, obj, id, DISPATCH_PROPERTYPUT, &dp);
    }
    if(FAILED(hres))
        return hres;

    stack_popn(ctx, arg_cnt+2);
    return S_OK;
}