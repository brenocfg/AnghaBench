#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ jsop_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_12__ {TYPE_5__* argument_list; TYPE_7__* expression; } ;
typedef  TYPE_3__ call_expression_t ;
struct TYPE_13__ {TYPE_7__* expression2; TYPE_7__* expression1; } ;
typedef  TYPE_4__ binary_expression_t ;
struct TYPE_14__ {TYPE_7__* expr; struct TYPE_14__* next; } ;
typedef  TYPE_5__ argument_t ;
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_11__ {TYPE_1__* arg; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
struct TYPE_10__ {unsigned int uint; int lng; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ EXPR_CALL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 unsigned int JS_E_ILLEGAL_ASSIGN ; 
 scalar_t__ OP_LAST ; 
 scalar_t__ OP_assign ; 
 int /*<<< orphan*/  OP_assign_call ; 
 scalar_t__ OP_call_member ; 
 scalar_t__ OP_push_acc ; 
 scalar_t__ OP_refval ; 
 int /*<<< orphan*/  OP_throw_ref ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  compile_memberid_expression (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdexNameEnsure ; 
 TYPE_6__* instr_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ is_memberid_expr (scalar_t__) ; 
 unsigned int push_instr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT compile_assign_expression(compiler_ctx_t *ctx, binary_expression_t *expr, jsop_t op)
{
    BOOL use_throw_path = FALSE;
    unsigned arg_cnt = 0;
    HRESULT hres;

    if(expr->expression1->type == EXPR_CALL) {
        call_expression_t *call_expr = (call_expression_t*)expr->expression1;
        argument_t *arg;

        if(is_memberid_expr(call_expr->expression->type) && call_expr->argument_list) {
            hres = compile_memberid_expression(ctx, call_expr->expression, fdexNameEnsure);
            if(FAILED(hres))
                return hres;

            for(arg = call_expr->argument_list; arg; arg = arg->next) {
                hres = compile_expression(ctx, arg->expr, TRUE);
                if(FAILED(hres))
                    return hres;
                arg_cnt++;
            }

            if(op != OP_LAST) {
                unsigned instr;

                /* We need to call the functions twice: to get the value and to set it.
                 * JavaScript interpreted functions may to modify value on the stack,
                 * but assignment calls are allowed only on external functions, so we
                 * may reuse the stack here. */
                instr = push_instr(ctx, OP_call_member);
                if(!instr)
                    return E_OUTOFMEMORY;
                instr_ptr(ctx, instr)->u.arg[0].uint = arg_cnt;
                instr_ptr(ctx, instr)->u.arg[1].lng = 1;

                if(!push_instr(ctx, OP_push_acc))
                    return E_OUTOFMEMORY;
            }
        }else {
            use_throw_path = TRUE;
        }
    }else if(is_memberid_expr(expr->expression1->type)) {
        hres = compile_memberid_expression(ctx, expr->expression1, fdexNameEnsure);
        if(FAILED(hres))
            return hres;
        if(op != OP_LAST && !push_instr(ctx, OP_refval))
            return E_OUTOFMEMORY;
    }else {
        use_throw_path = TRUE;
    }

    if(use_throw_path) {
        /* Illegal assignment: evaluate and throw */
        hres = compile_expression(ctx, expr->expression1, TRUE);
        if(FAILED(hres))
            return hres;

        hres = compile_expression(ctx, expr->expression2, TRUE);
        if(FAILED(hres))
            return hres;

        if(op != OP_LAST && !push_instr(ctx, op))
            return E_OUTOFMEMORY;

        return push_instr_uint(ctx, OP_throw_ref, JS_E_ILLEGAL_ASSIGN);
    }

    hres = compile_expression(ctx, expr->expression2, TRUE);
    if(FAILED(hres))
        return hres;

    if(op != OP_LAST && !push_instr(ctx, op))
        return E_OUTOFMEMORY;

    if(arg_cnt)
        return push_instr_uint(ctx, OP_assign_call, arg_cnt);

    if(!push_instr(ctx, OP_assign))
        return E_OUTOFMEMORY;

    return S_OK;
}