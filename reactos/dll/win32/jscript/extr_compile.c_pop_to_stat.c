#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ stack_use; scalar_t__ using_except; scalar_t__ using_scope; struct TYPE_7__* next; } ;
typedef  TYPE_1__ statement_ctx_t ;
struct TYPE_8__ {int code_off; TYPE_1__* stat_ctx; } ;
typedef  TYPE_2__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_pop ; 
 int /*<<< orphan*/  OP_pop_except ; 
 int /*<<< orphan*/  OP_pop_scope ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  push_instr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_uint (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT pop_to_stat(compiler_ctx_t *ctx, statement_ctx_t *stat_ctx)
{
    unsigned stack_pop = 0;
    statement_ctx_t *iter;
    HRESULT hres;

    for(iter = ctx->stat_ctx; iter != stat_ctx; iter = iter->next) {
        if(iter->using_scope && !push_instr(ctx, OP_pop_scope))
            return E_OUTOFMEMORY;
        if(iter->using_except) {
            if(stack_pop) {
                hres = push_instr_uint(ctx, OP_pop, stack_pop);
                if(FAILED(hres))
                    return hres;
                stack_pop = 0;
            }
            hres = push_instr_uint(ctx, OP_pop_except, ctx->code_off+1);
            if(FAILED(hres))
                return hres;
        }
        stack_pop += iter->stack_use;
    }

    if(stack_pop) {
        hres = push_instr_uint(ctx, OP_pop, stack_pop);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}