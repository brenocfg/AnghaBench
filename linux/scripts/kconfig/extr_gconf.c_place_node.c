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
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int indent ; 
 int /*<<< orphan*/ ** parents ; 
 int /*<<< orphan*/  set_node (int /*<<< orphan*/ *,struct menu*,char**) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void place_node(struct menu *menu, char **row)
{
	GtkTreeIter *parent = parents[indent - 1];
	GtkTreeIter *node = parents[indent];

	gtk_tree_store_append(tree, node, parent);
	set_node(node, menu, row);
}