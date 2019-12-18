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
typedef  int /*<<< orphan*/  compile_ctx_t ;
struct TYPE_3__ {int /*<<< orphan*/  value_expr; int /*<<< orphan*/  member_expr; } ;
typedef  TYPE_1__ assign_statement_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  compile_assignment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_assign_statement(compile_ctx_t *ctx, assign_statement_t *stat, BOOL is_set)
{
    return compile_assignment(ctx, stat->member_expr, stat->value_expr, is_set);
}