#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  pull_exec_paramids_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static Bitmapset *
pull_exec_paramids(Expr *expr)
{
	Bitmapset  *result = NULL;

	(void) pull_exec_paramids_walker((Node *) expr, &result);

	return result;
}