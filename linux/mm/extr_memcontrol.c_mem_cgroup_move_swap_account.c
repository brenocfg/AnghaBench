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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int mem_cgroup_move_swap_account(swp_entry_t entry,
				struct mem_cgroup *from, struct mem_cgroup *to)
{
	return -EINVAL;
}