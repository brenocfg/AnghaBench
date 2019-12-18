#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int member_0; int /*<<< orphan*/  for_end_label; } ;
typedef  TYPE_1__ statement_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  identifier; int /*<<< orphan*/  body; int /*<<< orphan*/  group_expr; } ;
typedef  TYPE_2__ foreach_statement_t ;
struct TYPE_17__ {unsigned int instr_cnt; } ;
typedef  TYPE_3__ compile_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_empty ; 
 int /*<<< orphan*/  OP_enumnext ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_newenum ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  alloc_label (TYPE_3__*) ; 
 int /*<<< orphan*/  compile_expression (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_statement (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_catch (TYPE_3__*,int) ; 
 int /*<<< orphan*/  label_set_addr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_addr (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  push_instr_uint_bstr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_foreach_statement(compile_ctx_t *ctx, foreach_statement_t *stat)
{
    statement_ctx_t loop_ctx = {1};
    unsigned loop_start;
    HRESULT hres;

    /* Preserve a place on the stack in case we throw before having proper enum collection. */
    if(!push_instr(ctx, OP_empty))
        return E_OUTOFMEMORY;

    hres = compile_expression(ctx, stat->group_expr);
    if(FAILED(hres))
        return hres;

    if(!push_instr(ctx, OP_newenum))
        return E_OUTOFMEMORY;

    if(!(loop_ctx.for_end_label = alloc_label(ctx)))
        return E_OUTOFMEMORY;

    hres = push_instr_uint_bstr(ctx, OP_enumnext, loop_ctx.for_end_label, stat->identifier);
    if(FAILED(hres))
        return hres;

    if(!emit_catch(ctx, 1))
        return E_OUTOFMEMORY;

    loop_start = ctx->instr_cnt;
    hres = compile_statement(ctx, &loop_ctx, stat->body);
    if(FAILED(hres))
        return hres;

    /* We need a separated enumnext here, because we need to jump out of the loop on exception. */
    hres = push_instr_uint_bstr(ctx, OP_enumnext, loop_ctx.for_end_label, stat->identifier);
    if(FAILED(hres))
        return hres;

    hres = push_instr_addr(ctx, OP_jmp, loop_start);
    if(FAILED(hres))
        return hres;

    label_set_addr(ctx, loop_ctx.for_end_label);
    return S_OK;
}