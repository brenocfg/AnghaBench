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

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_clear (scalar_t__) ; 
 int /*<<< orphan*/  gtk_tree_view_expand_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rootmenu ; 
 scalar_t__ tree ; 
 scalar_t__ tree1 ; 
 int /*<<< orphan*/  tree1_w ; 
 scalar_t__ tree2 ; 

__attribute__((used)) static void display_list(void)
{
	if (tree1)
		gtk_tree_store_clear(tree1);

	tree = tree1;
	display_tree(&rootmenu);
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree1_w));
	tree = tree2;
}