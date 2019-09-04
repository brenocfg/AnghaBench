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
struct mem_cgroup {int /*<<< orphan*/  css; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 struct mem_cgroup* root_mem_cgroup ; 

void mem_cgroup_iter_break(struct mem_cgroup *root,
			   struct mem_cgroup *prev)
{
	if (!root)
		root = root_mem_cgroup;
	if (prev && prev != root)
		css_put(&prev->css);
}