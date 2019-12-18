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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 int /*<<< orphan*/  uncharge_list (struct list_head*) ; 

void mem_cgroup_uncharge_list(struct list_head *page_list)
{
	if (mem_cgroup_disabled())
		return;

	if (!list_empty(page_list))
		uncharge_list(page_list);
}