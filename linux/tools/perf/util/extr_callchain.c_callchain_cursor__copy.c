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
struct callchain_cursor_node {int /*<<< orphan*/  srcline; int /*<<< orphan*/  branch_from; int /*<<< orphan*/  iter_cycles; int /*<<< orphan*/  nr_loop_iter; int /*<<< orphan*/  branch_flags; int /*<<< orphan*/  branch; int /*<<< orphan*/  sym; int /*<<< orphan*/  map; int /*<<< orphan*/  ip; } ;
struct callchain_cursor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  callchain_cursor_advance (struct callchain_cursor*) ; 
 int callchain_cursor_append (struct callchain_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cursor_commit (struct callchain_cursor*) ; 
 struct callchain_cursor_node* callchain_cursor_current (struct callchain_cursor*) ; 
 int /*<<< orphan*/  callchain_cursor_reset (struct callchain_cursor*) ; 

int callchain_cursor__copy(struct callchain_cursor *dst,
			   struct callchain_cursor *src)
{
	int rc = 0;

	callchain_cursor_reset(dst);
	callchain_cursor_commit(src);

	while (true) {
		struct callchain_cursor_node *node;

		node = callchain_cursor_current(src);
		if (node == NULL)
			break;

		rc = callchain_cursor_append(dst, node->ip, node->map, node->sym,
					     node->branch, &node->branch_flags,
					     node->nr_loop_iter,
					     node->iter_cycles,
					     node->branch_from, node->srcline);
		if (rc)
			break;

		callchain_cursor_advance(src);
	}

	return rc;
}