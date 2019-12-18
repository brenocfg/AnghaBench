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
struct gcov_node {int num_loaded; scalar_t__* loaded_info; scalar_t__ unloaded_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcov_info_reset (scalar_t__) ; 

__attribute__((used)) static void reset_node(struct gcov_node *node)
{
	int i;

	if (node->unloaded_info)
		gcov_info_reset(node->unloaded_info);
	for (i = 0; i < node->num_loaded; i++)
		gcov_info_reset(node->loaded_info[i]);
}