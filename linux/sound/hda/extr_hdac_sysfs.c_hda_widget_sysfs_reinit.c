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
struct hdac_widget_tree {int /*<<< orphan*/  root; struct hdac_widget_tree* nodes; } ;
struct hdac_device {scalar_t__ start_nid; int num_nodes; scalar_t__ end_nid; struct hdac_widget_tree* widgets; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  add_widget_node (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct hdac_widget_tree*) ; 
 int /*<<< orphan*/  free_widget_node (struct hdac_widget_tree,int /*<<< orphan*/ *) ; 
 struct hdac_widget_tree* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hdac_widget_tree*) ; 
 struct hdac_widget_tree* kmemdup (struct hdac_widget_tree*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_node_group ; 

int hda_widget_sysfs_reinit(struct hdac_device *codec,
			    hda_nid_t start_nid, int num_nodes)
{
	struct hdac_widget_tree *tree;
	hda_nid_t end_nid = start_nid + num_nodes;
	hda_nid_t nid;
	int i;

	if (!codec->widgets)
		return 0;

	tree = kmemdup(codec->widgets, sizeof(*tree), GFP_KERNEL);
	if (!tree)
		return -ENOMEM;

	tree->nodes = kcalloc(num_nodes + 1, sizeof(*tree->nodes), GFP_KERNEL);
	if (!tree->nodes) {
		kfree(tree);
		return -ENOMEM;
	}

	/* prune non-existing nodes */
	for (i = 0, nid = codec->start_nid; i < codec->num_nodes; i++, nid++) {
		if (nid < start_nid || nid >= end_nid)
			free_widget_node(codec->widgets->nodes[i],
					 &widget_node_group);
	}

	/* add new nodes */
	for (i = 0, nid = start_nid; i < num_nodes; i++, nid++) {
		if (nid < codec->start_nid || nid >= codec->end_nid)
			add_widget_node(tree->root, nid, &widget_node_group,
					&tree->nodes[i]);
		else
			tree->nodes[i] =
				codec->widgets->nodes[nid - codec->start_nid];
	}

	/* replace with the new tree */
	kfree(codec->widgets->nodes);
	kfree(codec->widgets);
	codec->widgets = tree;

	kobject_uevent(tree->root, KOBJ_CHANGE);
	return 0;
}