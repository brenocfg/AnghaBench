#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  with_statement_t ;
typedef  int /*<<< orphan*/  while_statement_t ;
typedef  int /*<<< orphan*/  var_statement_t ;
typedef  int /*<<< orphan*/  try_statement_t ;
typedef  int /*<<< orphan*/  switch_statement_t ;
struct TYPE_23__ {int type; } ;
typedef  TYPE_1__ statement_t ;
struct TYPE_24__ {struct TYPE_24__* next; } ;
typedef  TYPE_2__ statement_ctx_t ;
typedef  int /*<<< orphan*/  labelled_statement_t ;
typedef  int /*<<< orphan*/  if_statement_t ;
typedef  int /*<<< orphan*/  forin_statement_t ;
typedef  int /*<<< orphan*/  for_statement_t ;
typedef  int /*<<< orphan*/  expression_statement_t ;
struct TYPE_25__ {TYPE_2__* stat_ctx; } ;
typedef  TYPE_3__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  branch_statement_t ;
struct TYPE_26__ {int /*<<< orphan*/  stat_list; } ;
typedef  TYPE_4__ block_statement_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
#define  STAT_BLOCK 143 
#define  STAT_BREAK 142 
#define  STAT_CONTINUE 141 
#define  STAT_EMPTY 140 
#define  STAT_EXPR 139 
#define  STAT_FOR 138 
#define  STAT_FORIN 137 
#define  STAT_IF 136 
#define  STAT_LABEL 135 
#define  STAT_RETURN 134 
#define  STAT_SWITCH 133 
#define  STAT_THROW 132 
#define  STAT_TRY 131 
#define  STAT_VAR 130 
#define  STAT_WHILE 129 
#define  STAT_WITH 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compile_block_statement (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_break_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_continue_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_expression_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_for_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_forin_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_if_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_labelled_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_return_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_switch_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_throw_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_try_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_var_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_while_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_with_statement (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT compile_statement(compiler_ctx_t *ctx, statement_ctx_t *stat_ctx, statement_t *stat)
{
    HRESULT hres;

    if(stat_ctx) {
        stat_ctx->next = ctx->stat_ctx;
        ctx->stat_ctx = stat_ctx;
    }

    switch(stat->type) {
    case STAT_BLOCK:
        hres = compile_block_statement(ctx, ((block_statement_t*)stat)->stat_list);
        break;
    case STAT_BREAK:
        hres = compile_break_statement(ctx, (branch_statement_t*)stat);
        break;
    case STAT_CONTINUE:
        hres = compile_continue_statement(ctx, (branch_statement_t*)stat);
        break;
    case STAT_EMPTY:
        /* nothing to do */
        hres = S_OK;
        break;
    case STAT_EXPR:
        hres = compile_expression_statement(ctx, (expression_statement_t*)stat);
        break;
    case STAT_FOR:
        hres = compile_for_statement(ctx, (for_statement_t*)stat);
        break;
    case STAT_FORIN:
        hres = compile_forin_statement(ctx, (forin_statement_t*)stat);
        break;
    case STAT_IF:
        hres = compile_if_statement(ctx, (if_statement_t*)stat);
        break;
    case STAT_LABEL:
        hres = compile_labelled_statement(ctx, (labelled_statement_t*)stat);
        break;
    case STAT_RETURN:
        hres = compile_return_statement(ctx, (expression_statement_t*)stat);
        break;
    case STAT_SWITCH:
        hres = compile_switch_statement(ctx, (switch_statement_t*)stat);
        break;
    case STAT_THROW:
        hres = compile_throw_statement(ctx, (expression_statement_t*)stat);
        break;
    case STAT_TRY:
        hres = compile_try_statement(ctx, (try_statement_t*)stat);
        break;
    case STAT_VAR:
        hres = compile_var_statement(ctx, (var_statement_t*)stat);
        break;
    case STAT_WHILE:
        hres = compile_while_statement(ctx, (while_statement_t*)stat);
        break;
    case STAT_WITH:
        hres = compile_with_statement(ctx, (with_statement_t*)stat);
        break;
    DEFAULT_UNREACHABLE;
    }

    if(stat_ctx) {
        assert(ctx->stat_ctx == stat_ctx);
        ctx->stat_ctx = stat_ctx->next;
    }

    return hres;
}