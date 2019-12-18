#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* case_clausules; TYPE_2__* expr; } ;
typedef  TYPE_1__ select_statement_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ expression_t ;
typedef  int /*<<< orphan*/  compile_ctx_t ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  stat; TYPE_2__* expr; } ;
typedef  TYPE_3__ case_clausule_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_case ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_pop ; 
 int /*<<< orphan*/  OP_val ; 
 int /*<<< orphan*/  S_OK ; 
 unsigned int alloc_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  compile_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_catch_jmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int* heap_alloc (unsigned int) ; 
 int /*<<< orphan*/  heap_free (unsigned int*) ; 
 int /*<<< orphan*/  label_set_addr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT compile_select_statement(compile_ctx_t *ctx, select_statement_t *stat)
{
    unsigned end_label, case_cnt = 0, *case_labels = NULL, i;
    case_clausule_t *case_iter;
    expression_t *expr_iter;
    HRESULT hres;

    hres = compile_expression(ctx, stat->expr);
    if(FAILED(hres))
        return hres;

    if(!push_instr(ctx, OP_val))
        return E_OUTOFMEMORY;

    end_label = alloc_label(ctx);
    if(!end_label)
        return E_OUTOFMEMORY;

    if(!emit_catch_jmp(ctx, 0, end_label))
        return E_OUTOFMEMORY;

    for(case_iter = stat->case_clausules; case_iter; case_iter = case_iter->next)
        case_cnt++;

    if(case_cnt) {
        case_labels = heap_alloc(case_cnt*sizeof(*case_labels));
        if(!case_labels)
            return E_OUTOFMEMORY;
    }

    for(case_iter = stat->case_clausules, i=0; case_iter; case_iter = case_iter->next, i++) {
        case_labels[i] = alloc_label(ctx);
        if(!case_labels[i]) {
            hres = E_OUTOFMEMORY;
            break;
        }

        if(!case_iter->expr)
            break;

        for(expr_iter = case_iter->expr; expr_iter; expr_iter = expr_iter->next) {
            hres = compile_expression(ctx, expr_iter);
            if(FAILED(hres))
                break;

            hres = push_instr_addr(ctx, OP_case, case_labels[i]);
            if(FAILED(hres))
                break;

            if(!emit_catch_jmp(ctx, 0, case_labels[i])) {
                hres = E_OUTOFMEMORY;
                break;
            }
        }
    }

    if(FAILED(hres)) {
        heap_free(case_labels);
        return hres;
    }

    hres = push_instr_uint(ctx, OP_pop, 1);
    if(FAILED(hres)) {
        heap_free(case_labels);
        return hres;
    }

    hres = push_instr_addr(ctx, OP_jmp, case_iter ? case_labels[i] : end_label);
    if(FAILED(hres)) {
        heap_free(case_labels);
        return hres;
    }

    for(case_iter = stat->case_clausules, i=0; case_iter; case_iter = case_iter->next, i++) {
        label_set_addr(ctx, case_labels[i]);
        hres = compile_statement(ctx, NULL, case_iter->stat);
        if(FAILED(hres))
            break;

        if(!case_iter->next)
            break;

        hres = push_instr_addr(ctx, OP_jmp, end_label);
        if(FAILED(hres))
            break;
    }

    heap_free(case_labels);
    if(FAILED(hres))
        return hres;

    label_set_addr(ctx, end_label);
    return S_OK;
}