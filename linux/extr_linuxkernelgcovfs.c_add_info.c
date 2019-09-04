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
struct gcov_node {int num_loaded; struct gcov_info** loaded_info; struct gcov_info* unloaded_info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gcov_info_filename (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_info_free (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_info_is_compatible (struct gcov_info*,struct gcov_info*) ; 
 struct gcov_info** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gcov_info**) ; 
 int /*<<< orphan*/  memcpy (struct gcov_info**,struct gcov_info**,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_info(struct gcov_node *node, struct gcov_info *info)
{
	struct gcov_info **loaded_info;
	int num = node->num_loaded;

	/*
	 * Prepare new array. This is done first to simplify cleanup in
	 * case the new data set is incompatible, the node only contains
	 * unloaded data sets and there's not enough memory for the array.
	 */
	loaded_info = kcalloc(num + 1, sizeof(struct gcov_info *), GFP_KERNEL);
	if (!loaded_info) {
		pr_warn("could not add '%s' (out of memory)\n",
			gcov_info_filename(info));
		return;
	}
	memcpy(loaded_info, node->loaded_info,
	       num * sizeof(struct gcov_info *));
	loaded_info[num] = info;
	/* Check if the new data set is compatible. */
	if (num == 0) {
		/*
		 * A module was unloaded, modified and reloaded. The new
		 * data set replaces the copy of the last one.
		 */
		if (!gcov_info_is_compatible(node->unloaded_info, info)) {
			pr_warn("discarding saved data for %s "
				"(incompatible version)\n",
				gcov_info_filename(info));
			gcov_info_free(node->unloaded_info);
			node->unloaded_info = NULL;
		}
	} else {
		/*
		 * Two different versions of the same object file are loaded.
		 * The initial one takes precedence.
		 */
		if (!gcov_info_is_compatible(node->loaded_info[0], info)) {
			pr_warn("could not add '%s' (incompatible "
				"version)\n", gcov_info_filename(info));
			kfree(loaded_info);
			return;
		}
	}
	/* Overwrite previous array. */
	kfree(node->loaded_info);
	node->loaded_info = loaded_info;
	node->num_loaded = num + 1;
}