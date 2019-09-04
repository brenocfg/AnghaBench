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
struct gcov_node {scalar_t__ num_loaded; struct gcov_info* unloaded_info; struct gcov_info** loaded_info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct gcov_info *get_node_info(struct gcov_node *node)
{
	if (node->num_loaded > 0)
		return node->loaded_info[0];

	return node->unloaded_info;
}