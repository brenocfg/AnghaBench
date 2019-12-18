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
struct xa_node {scalar_t__ count; scalar_t__ nr_values; int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shadow_nodes ; 

__attribute__((used)) static void test_update_node(struct xa_node *node)
{
	if (node->count && node->count == node->nr_values) {
		if (list_empty(&node->private_list))
			list_add(&shadow_nodes, &node->private_list);
	} else {
		if (!list_empty(&node->private_list))
			list_del_init(&node->private_list);
	}
}