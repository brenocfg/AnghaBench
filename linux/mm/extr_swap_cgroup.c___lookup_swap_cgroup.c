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
struct swap_cgroup_ctrl {struct page** map; } ;
struct swap_cgroup {int dummy; } ;
struct page {int dummy; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 size_t SC_PER_PAGE ; 
 struct swap_cgroup* page_address (struct page*) ; 

__attribute__((used)) static struct swap_cgroup *__lookup_swap_cgroup(struct swap_cgroup_ctrl *ctrl,
						pgoff_t offset)
{
	struct page *mappage;
	struct swap_cgroup *sc;

	mappage = ctrl->map[offset / SC_PER_PAGE];
	sc = page_address(mappage);
	return sc + offset % SC_PER_PAGE;
}