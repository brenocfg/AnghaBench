#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ variable_list_t ;
struct TYPE_6__ {int /*<<< orphan*/  stat; int /*<<< orphan*/  variable_list; } ;
typedef  TYPE_2__ var_statement_t ;
typedef  int /*<<< orphan*/  statement_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_VAR ; 
 TYPE_2__* new_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static statement_t *new_var_statement(parser_ctx_t *ctx, variable_list_t *variable_list)
{
    var_statement_t *ret;

    ret = new_statement(ctx, STAT_VAR, sizeof(*ret));
    if(!ret)
        return NULL;

    ret->variable_list = variable_list->head;

    return &ret->stat;
}