#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statement_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_3__ {int /*<<< orphan*/  stat; int /*<<< orphan*/ * func_decl; } ;
typedef  TYPE_1__ function_statement_t ;
typedef  int /*<<< orphan*/  function_decl_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_FUNC ; 
 TYPE_1__* new_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static statement_t *new_function_statement(parser_ctx_t *ctx, function_decl_t *decl)
{
    function_statement_t *stat;

    stat = new_statement(ctx, STAT_FUNC, sizeof(*stat));
    if(!stat)
        return NULL;

    stat->func_decl = decl;
    return &stat->stat;
}