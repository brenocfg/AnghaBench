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
struct menu {int dummy; } ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  found ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct menu**,int) ; 
 scalar_t__ gtk_tree_model_iter_children (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  model2 ; 

GtkTreeIter *gtktree_iter_find_node(GtkTreeIter * parent,
				    struct menu *tofind)
{
	GtkTreeIter iter;
	GtkTreeIter *child = &iter;
	gboolean valid;
	GtkTreeIter *ret;

	valid = gtk_tree_model_iter_children(model2, child, parent);
	while (valid) {
		struct menu *menu;

		gtk_tree_model_get(model2, child, 6, &menu, -1);

		if (menu == tofind) {
			memcpy(&found, child, sizeof(GtkTreeIter));
			return &found;
		}

		ret = gtktree_iter_find_node(child, tofind);
		if (ret)
			return ret;

		valid = gtk_tree_model_iter_next(model2, child);
	}

	return NULL;
}