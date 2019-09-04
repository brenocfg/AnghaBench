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
struct tipc_node {int /*<<< orphan*/  link_cnt; struct tipc_link_entry* links; } ;
struct tipc_link_entry {int /*<<< orphan*/ * link; } ;

/* Variables and functions */
 int MAX_BEARERS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void  tipc_node_clear_links(struct tipc_node *node)
{
	int i;

	for (i = 0; i < MAX_BEARERS; i++) {
		struct tipc_link_entry *le = &node->links[i];

		if (le->link) {
			kfree(le->link);
			le->link = NULL;
			node->link_cnt--;
		}
	}
}