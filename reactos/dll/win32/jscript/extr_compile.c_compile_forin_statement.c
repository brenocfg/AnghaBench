#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int member_0; void* break_label; void* continue_label; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ statement_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  statement; TYPE_5__* expr; TYPE_3__* variable; int /*<<< orphan*/  in_expr; } ;
typedef  TYPE_2__ forin_statement_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  identifier; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_STARTENUM ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 void* JS_E_ILLEGAL_ASSIGN ; 
 int /*<<< orphan*/  OP_forin ; 
 int /*<<< orphan*/  OP_int ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_throw_ref ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 void* alloc_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_memberid_expression (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_statement (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_variable_list (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  emit_identifier_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdexNameEnsure ; 
 scalar_t__ is_memberid_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_set_addr (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  push_instr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static HRESULT compile_forin_statement(compiler_ctx_t *ctx, forin_statement_t *stat)
{
    statement_ctx_t stat_ctx = {4, FALSE, FALSE};
    HRESULT hres;

    if(stat->variable) {
        hres = compile_variable_list(ctx, stat->variable);
        if(FAILED(hres))
            return hres;
    }

    stat_ctx.break_label = alloc_label(ctx);
    if(!stat_ctx.break_label)
        return E_OUTOFMEMORY;

    stat_ctx.continue_label = alloc_label(ctx);
    if(!stat_ctx.continue_label)
        return E_OUTOFMEMORY;

    hres = compile_expression(ctx, stat->in_expr, TRUE);
    if(FAILED(hres))
        return hres;

    if(stat->variable) {
        hres = emit_identifier_ref(ctx, stat->variable->identifier, fdexNameEnsure);
        if(FAILED(hres))
            return hres;
    }else if(is_memberid_expr(stat->expr->type)) {
        hres = compile_memberid_expression(ctx, stat->expr, fdexNameEnsure);
        if(FAILED(hres))
            return hres;
    }else {
        hres = push_instr_uint(ctx, OP_throw_ref, JS_E_ILLEGAL_ASSIGN);
        if(FAILED(hres))
            return hres;

        /* FIXME: compile statement anyways when we depend on compiler to check errors */
        return S_OK;
    }

    hres = push_instr_int(ctx, OP_int, DISPID_STARTENUM);
    if(FAILED(hres))
        return hres;

    label_set_addr(ctx, stat_ctx.continue_label);
    hres = push_instr_uint(ctx, OP_forin, stat_ctx.break_label);
    if(FAILED(hres))
        return E_OUTOFMEMORY;

    hres = compile_statement(ctx, &stat_ctx, stat->statement);
    if(FAILED(hres))
        return hres;

    hres = push_instr_uint(ctx, OP_jmp, stat_ctx.continue_label);
    if(FAILED(hres))
        return hres;

    label_set_addr(ctx, stat_ctx.break_label);
    return S_OK;
}