#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  exprs; } ;
typedef  TYPE_1__ PathTarget ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  add_column_to_pathtarget (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_member (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
add_new_column_to_pathtarget(PathTarget *target, Expr *expr)
{
	if (!list_member(target->exprs, expr))
		add_column_to_pathtarget(target, expr, 0);
}