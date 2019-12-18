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
struct TYPE_3__ {int /*<<< orphan*/  stat; int /*<<< orphan*/ * decls; } ;
typedef  TYPE_1__ const_statement_t ;
typedef  int /*<<< orphan*/  const_decl_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_CONST ; 
 TYPE_1__* new_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static statement_t *new_const_statement(parser_ctx_t *ctx, const_decl_t *decls)
{
    const_statement_t *stat;

    stat = new_statement(ctx, STAT_CONST, sizeof(*stat));
    if(!stat)
        return NULL;

    stat->decls = decls;
    return &stat->stat;
}