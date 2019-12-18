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
struct gcov_node {scalar_t__ unloaded_info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcov_info_add (scalar_t__,struct gcov_info*) ; 
 scalar_t__ gcov_info_dup (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_info_filename (struct gcov_info*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void save_info(struct gcov_node *node, struct gcov_info *info)
{
	if (node->unloaded_info)
		gcov_info_add(node->unloaded_info, info);
	else {
		node->unloaded_info = gcov_info_dup(info);
		if (!node->unloaded_info) {
			pr_warn("could not save data for '%s' "
				"(out of memory)\n",
				gcov_info_filename(info));
		}
	}
}