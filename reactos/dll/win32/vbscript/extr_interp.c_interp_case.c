#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_3__ variant_val_t ;
struct TYPE_16__ {TYPE_2__* instr; } ;
typedef  TYPE_4__ exec_ctx_t ;
struct TYPE_13__ {unsigned int uint; } ;
struct TYPE_14__ {TYPE_1__ arg1; } ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const) ; 
 scalar_t__ VARCMP_EQ ; 
 int /*<<< orphan*/  instr_jmp (TYPE_4__*,unsigned int const) ; 
 int /*<<< orphan*/  release_val (TYPE_3__*) ; 
 scalar_t__ stack_pop_val (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stack_popn (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stack_top (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ var_cmp (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_case(exec_ctx_t *ctx)
{
    const unsigned arg = ctx->instr->arg1.uint;
    variant_val_t v;
    HRESULT hres;

    TRACE("%d\n", arg);

    hres = stack_pop_val(ctx, &v);
    if(FAILED(hres))
        return hres;

    hres = var_cmp(ctx, stack_top(ctx, 0), v.v);
    release_val(&v);
    if(FAILED(hres))
        return hres;

    if(hres == VARCMP_EQ) {
        stack_popn(ctx, 1);
        instr_jmp(ctx, arg);
    }else {
        ctx->instr++;
    }

    return S_OK;
}