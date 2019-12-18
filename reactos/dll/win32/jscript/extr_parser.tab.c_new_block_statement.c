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
typedef  int /*<<< orphan*/  statement_t ;
struct TYPE_5__ {int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ statement_list_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  stat; int /*<<< orphan*/ * stat_list; } ;
typedef  TYPE_2__ block_statement_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_BLOCK ; 
 TYPE_2__* new_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static statement_t *new_block_statement(parser_ctx_t *ctx, statement_list_t *list)
{
    block_statement_t *ret;

    ret = new_statement(ctx, STAT_BLOCK, sizeof(*ret));
    if(!ret)
        return NULL;

    ret->stat_list = list ? list->head : NULL;

    return &ret->stat;
}