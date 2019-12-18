#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int break_label; unsigned int continue_label; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ statement_ctx_t ;
struct TYPE_14__ {scalar_t__ end_expr; int /*<<< orphan*/  statement; scalar_t__ expr; scalar_t__ begin_expr; scalar_t__ variable_list; } ;
typedef  TYPE_2__ for_statement_t ;
struct TYPE_15__ {unsigned int code_off; } ;
typedef  TYPE_3__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_jmp_z ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 void* alloc_label (TYPE_3__*) ; 
 int /*<<< orphan*/  compile_expression (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_statement (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_variable_list (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  label_set_addr (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  push_instr_uint (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT compile_for_statement(compiler_ctx_t *ctx, for_statement_t *stat)
{
    statement_ctx_t stat_ctx = {0, FALSE, FALSE};
    unsigned expr_off;
    HRESULT hres;

    if(stat->variable_list) {
        hres = compile_variable_list(ctx, stat->variable_list);
        if(FAILED(hres))
            return hres;
    }else if(stat->begin_expr) {
        hres = compile_expression(ctx, stat->begin_expr, FALSE);
        if(FAILED(hres))
            return hres;
    }

    stat_ctx.break_label = alloc_label(ctx);
    if(!stat_ctx.break_label)
        return E_OUTOFMEMORY;

    stat_ctx.continue_label = alloc_label(ctx);
    if(!stat_ctx.continue_label)
        return E_OUTOFMEMORY;

    expr_off = ctx->code_off;

    if(stat->expr) {
        hres = compile_expression(ctx, stat->expr, TRUE);
        if(FAILED(hres))
            return hres;

        hres = push_instr_uint(ctx, OP_jmp_z, stat_ctx.break_label);
        if(FAILED(hres))
            return hres;
    }

    hres = compile_statement(ctx, &stat_ctx, stat->statement);
    if(FAILED(hres))
        return hres;

    label_set_addr(ctx, stat_ctx.continue_label);

    if(stat->end_expr) {
        hres = compile_expression(ctx, stat->end_expr, FALSE);
        if(FAILED(hres))
            return hres;
    }

    hres = push_instr_uint(ctx, OP_jmp, expr_off);
    if(FAILED(hres))
        return hres;

    label_set_addr(ctx, stat_ctx.break_label);
    return S_OK;
}