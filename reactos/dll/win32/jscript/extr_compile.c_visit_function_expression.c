#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  identifier; scalar_t__ event_target; struct TYPE_8__* next; scalar_t__ func_id; } ;
typedef  TYPE_2__ function_expression_t ;
struct TYPE_9__ {TYPE_2__* func_head; TYPE_2__* func_tail; TYPE_1__* func; } ;
typedef  TYPE_3__ compiler_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  func_cnt; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ alloc_variable (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT visit_function_expression(compiler_ctx_t *ctx, function_expression_t *expr)
{
    expr->func_id = ctx->func->func_cnt++;
    ctx->func_tail = ctx->func_tail ? (ctx->func_tail->next = expr) : (ctx->func_head = expr);

    return !expr->identifier || expr->event_target || alloc_variable(ctx, expr->identifier)
        ? S_OK : E_OUTOFMEMORY;
}