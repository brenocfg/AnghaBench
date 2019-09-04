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
struct o2nm_node {int /*<<< orphan*/  nd_item; } ;

/* Variables and functions */
 int EINVAL ; 
 int o2nm_depend_item (int /*<<< orphan*/ *) ; 
 struct o2nm_node* o2nm_get_node_by_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2nm_node_put (struct o2nm_node*) ; 
 int /*<<< orphan*/  o2nm_this_node () ; 

int o2nm_depend_this_node(void)
{
	int ret = 0;
	struct o2nm_node *local_node;

	local_node = o2nm_get_node_by_num(o2nm_this_node());
	if (!local_node) {
		ret = -EINVAL;
		goto out;
	}

	ret = o2nm_depend_item(&local_node->nd_item);
	o2nm_node_put(local_node);

out:
	return ret;
}