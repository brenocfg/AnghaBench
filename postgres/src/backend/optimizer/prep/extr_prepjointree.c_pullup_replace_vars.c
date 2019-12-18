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
struct TYPE_3__ {int /*<<< orphan*/  outer_hasSubLinks; int /*<<< orphan*/  varno; } ;
typedef  TYPE_1__ pullup_replace_vars_context ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  pullup_replace_vars_callback ; 
 int /*<<< orphan*/ * replace_rte_variables (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
pullup_replace_vars(Node *expr, pullup_replace_vars_context *context)
{
	return replace_rte_variables(expr,
								 context->varno, 0,
								 pullup_replace_vars_callback,
								 (void *) context,
								 context->outer_hasSubLinks);
}