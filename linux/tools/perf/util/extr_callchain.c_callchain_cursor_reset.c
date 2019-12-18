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
struct callchain_cursor_node {int /*<<< orphan*/  map; struct callchain_cursor_node* next; } ;
struct callchain_cursor {struct callchain_cursor_node* first; struct callchain_cursor_node** last; scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  map__zput (int /*<<< orphan*/ ) ; 

void callchain_cursor_reset(struct callchain_cursor *cursor)
{
	struct callchain_cursor_node *node;

	cursor->nr = 0;
	cursor->last = &cursor->first;

	for (node = cursor->first; node != NULL; node = node->next)
		map__zput(node->map);
}