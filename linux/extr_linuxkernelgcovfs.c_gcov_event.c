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
struct gcov_node {int dummy; } ;
struct gcov_info {int dummy; } ;
typedef  enum gcov_action { ____Placeholder_gcov_action } gcov_action ;

/* Variables and functions */
#define  GCOV_ADD 129 
#define  GCOV_REMOVE 128 
 int /*<<< orphan*/  add_info (struct gcov_node*,struct gcov_info*) ; 
 int /*<<< orphan*/  add_node (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_info_filename (struct gcov_info*) ; 
 struct gcov_node* get_node_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_lock ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_info (struct gcov_node*,struct gcov_info*) ; 

void gcov_event(enum gcov_action action, struct gcov_info *info)
{
	struct gcov_node *node;

	mutex_lock(&node_lock);
	node = get_node_by_name(gcov_info_filename(info));
	switch (action) {
	case GCOV_ADD:
		if (node)
			add_info(node, info);
		else
			add_node(info);
		break;
	case GCOV_REMOVE:
		if (node)
			remove_info(node, info);
		else {
			pr_warn("could not remove '%s' (not found)\n",
				gcov_info_filename(info));
		}
		break;
	}
	mutex_unlock(&node_lock);
}