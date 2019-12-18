#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ type; } ;
typedef  TYPE_4__ ref_t ;
struct TYPE_16__ {TYPE_1__* func; TYPE_3__* instr; } ;
typedef  TYPE_5__ exec_ctx_t ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_13__ {int /*<<< orphan*/  bstr; } ;
struct TYPE_14__ {TYPE_2__ arg1; } ;
struct TYPE_12__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FUNC_GLOBAL ; 
 scalar_t__ REF_NONE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VBDISP_CALLGET ; 
 int /*<<< orphan*/  add_dynamic_var (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_identifier (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stack_assume_val (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stack_pop (TYPE_5__*) ; 

__attribute__((used)) static HRESULT interp_const(exec_ctx_t *ctx)
{
    BSTR arg = ctx->instr->arg1.bstr;
    VARIANT *v;
    ref_t ref;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(arg));

    assert(ctx->func->type == FUNC_GLOBAL);

    hres = lookup_identifier(ctx, arg, VBDISP_CALLGET, &ref);
    if(FAILED(hres))
        return hres;

    if(ref.type != REF_NONE) {
        FIXME("%s already defined\n", debugstr_w(arg));
        return E_FAIL;
    }

    hres = stack_assume_val(ctx, 0);
    if(FAILED(hres))
        return hres;

    hres = add_dynamic_var(ctx, arg, TRUE, &v);
    if(FAILED(hres))
        return hres;

    *v = *stack_pop(ctx);
    return S_OK;
}