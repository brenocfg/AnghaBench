#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ current_pages; } ;

/* Variables and functions */
 int HZ ; 
 unsigned long MB2PAGES (int) ; 
 int /*<<< orphan*/  balloon_set_new_target (scalar_t__) ; 
 TYPE_1__ balloon_stats ; 
 unsigned long max_pfn ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 unsigned long selfballoon_downhysteresis ; 
 int selfballoon_interval ; 
 scalar_t__ selfballoon_min_usable_mb ; 
 int selfballoon_reserved_mb ; 
 unsigned long selfballoon_uphysteresis ; 
 int /*<<< orphan*/  selfballoon_worker ; 
 unsigned long totalram_pages ; 
 unsigned long totalreserve_pages ; 
 unsigned long vm_memory_committed () ; 
 scalar_t__ xen_selfballooning_enabled ; 

__attribute__((used)) static void selfballoon_process(struct work_struct *work)
{
	unsigned long cur_pages, goal_pages, tgt_pages, floor_pages;
	unsigned long useful_pages;
	bool reset_timer = false;

	if (xen_selfballooning_enabled) {
		cur_pages = totalram_pages;
		tgt_pages = cur_pages; /* default is no change */
		goal_pages = vm_memory_committed() +
				totalreserve_pages +
				MB2PAGES(selfballoon_reserved_mb);
#ifdef CONFIG_FRONTSWAP
		/* allow space for frontswap pages to be repatriated */
		if (frontswap_selfshrinking)
			goal_pages += frontswap_curr_pages();
#endif
		if (cur_pages > goal_pages)
			tgt_pages = cur_pages -
				((cur_pages - goal_pages) /
				  selfballoon_downhysteresis);
		else if (cur_pages < goal_pages)
			tgt_pages = cur_pages +
				((goal_pages - cur_pages) /
				  selfballoon_uphysteresis);
		/* else if cur_pages == goal_pages, no change */
		useful_pages = max_pfn - totalreserve_pages;
		if (selfballoon_min_usable_mb != 0)
			floor_pages = totalreserve_pages +
					MB2PAGES(selfballoon_min_usable_mb);
		/* piecewise linear function ending in ~3% slope */
		else if (useful_pages < MB2PAGES(16))
			floor_pages = max_pfn; /* not worth ballooning */
		else if (useful_pages < MB2PAGES(64))
			floor_pages = totalreserve_pages + MB2PAGES(16) +
					((useful_pages - MB2PAGES(16)) >> 1);
		else if (useful_pages < MB2PAGES(512))
			floor_pages = totalreserve_pages + MB2PAGES(40) +
					((useful_pages - MB2PAGES(40)) >> 3);
		else /* useful_pages >= MB2PAGES(512) */
			floor_pages = totalreserve_pages + MB2PAGES(99) +
					((useful_pages - MB2PAGES(99)) >> 5);
		if (tgt_pages < floor_pages)
			tgt_pages = floor_pages;
		balloon_set_new_target(tgt_pages +
			balloon_stats.current_pages - totalram_pages);
		reset_timer = true;
	}
#ifdef CONFIG_FRONTSWAP
	if (frontswap_selfshrinking) {
		frontswap_selfshrink();
		reset_timer = true;
	}
#endif
	if (reset_timer)
		schedule_delayed_work(&selfballoon_worker,
			selfballoon_interval * HZ);
}