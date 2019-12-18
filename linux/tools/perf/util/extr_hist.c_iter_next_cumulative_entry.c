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
struct hist_entry_iter {int /*<<< orphan*/  hide_unresolved; } ;
struct callchain_cursor_node {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  callchain_cursor ; 
 struct callchain_cursor_node* callchain_cursor_current (int /*<<< orphan*/ *) ; 
 int fill_callchain_info (struct addr_location*,struct callchain_cursor_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_next_cumulative_entry(struct hist_entry_iter *iter,
			   struct addr_location *al)
{
	struct callchain_cursor_node *node;

	node = callchain_cursor_current(&callchain_cursor);
	if (node == NULL)
		return 0;

	return fill_callchain_info(al, node, iter->hide_unresolved);
}