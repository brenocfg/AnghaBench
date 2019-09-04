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
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  mem_cgroup_throttle_swaprate (struct mem_cgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mem_cgroup_try_charge (struct page*,struct mm_struct*,int /*<<< orphan*/ ,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 

int mem_cgroup_try_charge_delay(struct page *page, struct mm_struct *mm,
			  gfp_t gfp_mask, struct mem_cgroup **memcgp,
			  bool compound)
{
	struct mem_cgroup *memcg;
	int ret;

	ret = mem_cgroup_try_charge(page, mm, gfp_mask, memcgp, compound);
	memcg = *memcgp;
	mem_cgroup_throttle_swaprate(memcg, page_to_nid(page), gfp_mask);
	return ret;
}