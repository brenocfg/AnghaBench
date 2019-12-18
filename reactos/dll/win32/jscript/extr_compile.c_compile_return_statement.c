#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ expr; } ;
typedef  TYPE_1__ expression_statement_t ;
struct TYPE_10__ {scalar_t__ from_eval; } ;
typedef  TYPE_2__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_MISPLACED_RETURN ; 
 int /*<<< orphan*/  OP_ret ; 
 int /*<<< orphan*/  OP_setret ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  compile_expression (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_to_stat (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_instr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_uint (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT compile_return_statement(compiler_ctx_t *ctx, expression_statement_t *stat)
{
    HRESULT hres;

    if(ctx->from_eval) {
        WARN("misplaced return statement\n");
        return JS_E_MISPLACED_RETURN;
    }

    if(stat->expr) {
        hres = compile_expression(ctx, stat->expr, TRUE);
        if(FAILED(hres))
            return hres;
        if(!push_instr(ctx, OP_setret))
            return E_OUTOFMEMORY;
    }

    hres = pop_to_stat(ctx, NULL);
    if(FAILED(hres))
        return hres;

    return push_instr_uint(ctx, OP_ret, !stat->expr);
}