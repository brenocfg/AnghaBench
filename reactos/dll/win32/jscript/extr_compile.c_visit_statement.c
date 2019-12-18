#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_7__* statement; int /*<<< orphan*/  expr; } ;
typedef  TYPE_2__ with_statement_t ;
struct TYPE_23__ {TYPE_7__* statement; int /*<<< orphan*/  expr; } ;
typedef  TYPE_3__ while_statement_t ;
struct TYPE_24__ {int /*<<< orphan*/  variable_list; } ;
typedef  TYPE_4__ var_statement_t ;
struct TYPE_25__ {TYPE_7__* finally_statement; TYPE_1__* catch_block; TYPE_7__* try_statement; } ;
typedef  TYPE_5__ try_statement_t ;
struct TYPE_26__ {TYPE_13__* case_list; int /*<<< orphan*/  expr; } ;
typedef  TYPE_6__ switch_statement_t ;
struct TYPE_27__ {int type; struct TYPE_27__* next; } ;
typedef  TYPE_7__ statement_t ;
struct TYPE_28__ {TYPE_7__* statement; } ;
typedef  TYPE_8__ labelled_statement_t ;
struct TYPE_29__ {TYPE_7__* else_stat; TYPE_7__* if_stat; int /*<<< orphan*/  expr; } ;
typedef  TYPE_9__ if_statement_t ;
struct TYPE_16__ {TYPE_7__* statement; int /*<<< orphan*/  expr; int /*<<< orphan*/  in_expr; int /*<<< orphan*/  variable; } ;
typedef  TYPE_10__ forin_statement_t ;
struct TYPE_17__ {int /*<<< orphan*/  end_expr; TYPE_7__* statement; int /*<<< orphan*/  expr; int /*<<< orphan*/  begin_expr; int /*<<< orphan*/  variable_list; } ;
typedef  TYPE_11__ for_statement_t ;
struct TYPE_18__ {int /*<<< orphan*/  expr; } ;
typedef  TYPE_12__ expression_statement_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_19__ {TYPE_7__* stat; struct TYPE_19__* next; int /*<<< orphan*/  expr; } ;
typedef  TYPE_13__ case_clausule_t ;
struct TYPE_20__ {int /*<<< orphan*/  stat_list; } ;
typedef  TYPE_14__ block_statement_t ;
struct TYPE_21__ {TYPE_7__* statement; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  visit_block_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visit_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visit_variable_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT visit_statement(compiler_ctx_t *ctx, statement_t *stat)
{
    HRESULT hres = S_OK;

    switch(stat->type) {
    case STAT_BLOCK:
        hres = visit_block_statement(ctx, ((block_statement_t*)stat)->stat_list);
        break;
    case STAT_BREAK:
    case STAT_CONTINUE:
    case STAT_EMPTY:
        break;
    case STAT_EXPR:
    case STAT_RETURN:
    case STAT_THROW: {
        expression_statement_t *expr_stat = (expression_statement_t*)stat;
        if(expr_stat->expr)
            hres = visit_expression(ctx, expr_stat->expr);
        break;
    }
    case STAT_FOR: {
        for_statement_t *for_stat = (for_statement_t*)stat;

        if(for_stat->variable_list)
            hres = visit_variable_list(ctx, for_stat->variable_list);
        else if(for_stat->begin_expr)
            hres = visit_expression(ctx, for_stat->begin_expr);
        if(FAILED(hres))
            break;

        if(for_stat->expr) {
            hres = visit_expression(ctx, for_stat->expr);
            if(FAILED(hres))
                break;
        }

        hres = visit_statement(ctx, for_stat->statement);
        if(FAILED(hres))
            break;

        if(for_stat->end_expr)
            hres = visit_expression(ctx, for_stat->end_expr);
        break;
    }
    case STAT_FORIN:  {
        forin_statement_t *forin_stat = (forin_statement_t*)stat;

        if(forin_stat->variable) {
            hres = visit_variable_list(ctx, forin_stat->variable);
            if(FAILED(hres))
                break;
        }

        hres = visit_expression(ctx, forin_stat->in_expr);
        if(FAILED(hres))
            return hres;

        if(forin_stat->expr) {
            hres = visit_expression(ctx, forin_stat->expr);
            if(FAILED(hres))
                return hres;
        }

        hres = visit_statement(ctx, forin_stat->statement);
        break;
    }
    case STAT_IF: {
        if_statement_t *if_stat = (if_statement_t*)stat;

        hres = visit_expression(ctx, if_stat->expr);
        if(FAILED(hres))
            return hres;

        hres = visit_statement(ctx, if_stat->if_stat);
        if(FAILED(hres))
            return hres;

        if(if_stat->else_stat)
            hres = visit_statement(ctx, if_stat->else_stat);
        break;
    }
    case STAT_LABEL:
        hres = visit_statement(ctx, ((labelled_statement_t*)stat)->statement);
        break;
    case STAT_SWITCH: {
        switch_statement_t *switch_stat = (switch_statement_t*)stat;
        statement_t *stat_iter;
        case_clausule_t *iter;

        hres = visit_expression(ctx, switch_stat->expr);
        if(FAILED(hres))
            return hres;

        for(iter = switch_stat->case_list; iter; iter = iter->next) {
            if(!iter->expr)
                continue;
            hres = visit_expression(ctx, iter->expr);
            if(FAILED(hres))
                return hres;
        }

        for(iter = switch_stat->case_list; iter; iter = iter->next) {
            while(iter->next && iter->next->stat == iter->stat)
                iter = iter->next;
            for(stat_iter = iter->stat; stat_iter && (!iter->next || iter->next->stat != stat_iter);
                stat_iter = stat_iter->next) {
                hres = visit_statement(ctx, stat_iter);
                if(FAILED(hres))
                    return hres;
            }
        }
        break;
    }
    case STAT_TRY: {
        try_statement_t *try_stat = (try_statement_t*)stat;

        hres = visit_statement(ctx, try_stat->try_statement);
        if(FAILED(hres))
            return hres;

        if(try_stat->catch_block) {
            hres = visit_statement(ctx, try_stat->catch_block->statement);
            if(FAILED(hres))
                return hres;
        }

        if(try_stat->finally_statement)
            hres = visit_statement(ctx, try_stat->finally_statement);
        break;
    }
    case STAT_VAR:
        hres = visit_variable_list(ctx, ((var_statement_t*)stat)->variable_list);
        break;
    case STAT_WHILE: {
        while_statement_t *while_stat = (while_statement_t*)stat;

        hres = visit_expression(ctx, while_stat->expr);
        if(FAILED(hres))
            return hres;

        hres = visit_statement(ctx, while_stat->statement);
        break;
    }
    case STAT_WITH: {
        with_statement_t *with_stat = (with_statement_t*)stat;

        hres = visit_expression(ctx, with_stat->expr);
        if(FAILED(hres))
            return hres;

        hres = visit_statement(ctx, with_stat->statement);
        break;
    }
    DEFAULT_UNREACHABLE;
    }

    return hres;
}