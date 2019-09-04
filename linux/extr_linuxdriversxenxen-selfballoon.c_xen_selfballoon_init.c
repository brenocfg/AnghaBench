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

/* Variables and functions */
 int ENODEV ; 
 int HZ ; 
 scalar_t__ PAGES2MB (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int selfballoon_interval ; 
 scalar_t__ selfballoon_reserved_mb ; 
 int /*<<< orphan*/  selfballoon_worker ; 
 scalar_t__ tmem_enabled ; 
 int totalram_pages ; 
 int /*<<< orphan*/  xen_domain () ; 
 scalar_t__ xen_initial_domain () ; 
 int xen_selfballooning_enabled ; 

int xen_selfballoon_init(bool use_selfballooning, bool use_frontswap_selfshrink)
{
	bool enable = false;
	unsigned long reserve_pages;

	if (!xen_domain())
		return -ENODEV;

	if (xen_initial_domain()) {
		pr_info("Xen selfballooning driver disabled for domain0\n");
		return -ENODEV;
	}

	xen_selfballooning_enabled = tmem_enabled && use_selfballooning;
	if (xen_selfballooning_enabled) {
		pr_info("Initializing Xen selfballooning driver\n");
		enable = true;
	}
#ifdef CONFIG_FRONTSWAP
	frontswap_selfshrinking = tmem_enabled && use_frontswap_selfshrink;
	if (frontswap_selfshrinking) {
		pr_info("Initializing frontswap selfshrinking driver\n");
		enable = true;
	}
#endif
	if (!enable)
		return -ENODEV;

	/*
	 * Give selfballoon_reserved_mb a default value(10% of total ram pages)
	 * to make selfballoon not so aggressive.
	 *
	 * There are mainly two reasons:
	 * 1) The original goal_page didn't consider some pages used by kernel
	 *    space, like slab pages and memory used by device drivers.
	 *
	 * 2) The balloon driver may not give back memory to guest OS fast
	 *    enough when the workload suddenly aquries a lot of physical memory.
	 *
	 * In both cases, the guest OS will suffer from memory pressure and
	 * OOM killer may be triggered.
	 * By reserving extra 10% of total ram pages, we can keep the system
	 * much more reliably and response faster in some cases.
	 */
	if (!selfballoon_reserved_mb) {
		reserve_pages = totalram_pages / 10;
		selfballoon_reserved_mb = PAGES2MB(reserve_pages);
	}
	schedule_delayed_work(&selfballoon_worker, selfballoon_interval * HZ);

	return 0;
}