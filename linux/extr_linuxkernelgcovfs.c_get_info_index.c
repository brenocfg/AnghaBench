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
struct gcov_node {int num_loaded; struct gcov_info** loaded_info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int get_info_index(struct gcov_node *node, struct gcov_info *info)
{
	int i;

	for (i = 0; i < node->num_loaded; i++) {
		if (node->loaded_info[i] == info)
			return i;
	}
	return -ENOENT;
}