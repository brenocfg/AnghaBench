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
struct gcov_node {int num_loaded; int /*<<< orphan*/  unloaded_info; int /*<<< orphan*/ * loaded_info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcov_info_filename (struct gcov_info*) ; 
 scalar_t__ gcov_persist ; 
 int get_info_index (struct gcov_node*,struct gcov_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_node (struct gcov_node*) ; 
 int /*<<< orphan*/  save_info (struct gcov_node*,struct gcov_info*) ; 

__attribute__((used)) static void remove_info(struct gcov_node *node, struct gcov_info *info)
{
	int i;

	i = get_info_index(node, info);
	if (i < 0) {
		pr_warn("could not remove '%s' (not found)\n",
			gcov_info_filename(info));
		return;
	}
	if (gcov_persist)
		save_info(node, info);
	/* Shrink array. */
	node->loaded_info[i] = node->loaded_info[node->num_loaded - 1];
	node->num_loaded--;
	if (node->num_loaded > 0)
		return;
	/* Last loaded data set was removed. */
	kfree(node->loaded_info);
	node->loaded_info = NULL;
	node->num_loaded = 0;
	if (!node->unloaded_info)
		remove_node(node);
}