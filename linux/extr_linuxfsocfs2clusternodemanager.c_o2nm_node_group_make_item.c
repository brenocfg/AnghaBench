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
struct config_item {int dummy; } ;
struct o2nm_node {struct config_item nd_item; int /*<<< orphan*/  nd_lock; int /*<<< orphan*/  nd_name; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ML_CLUSTER ; 
 scalar_t__ O2NM_MAX_NAME_LEN ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct o2nm_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  o2nm_node_type ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct config_item *o2nm_node_group_make_item(struct config_group *group,
						     const char *name)
{
	struct o2nm_node *node = NULL;

	if (strlen(name) > O2NM_MAX_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	node = kzalloc(sizeof(struct o2nm_node), GFP_KERNEL);
	if (node == NULL)
		return ERR_PTR(-ENOMEM);

	strcpy(node->nd_name, name); /* use item.ci_namebuf instead? */
	config_item_init_type_name(&node->nd_item, name, &o2nm_node_type);
	spin_lock_init(&node->nd_lock);

	mlog(ML_CLUSTER, "o2nm: Registering node %s\n", name);

	return &node->nd_item;
}