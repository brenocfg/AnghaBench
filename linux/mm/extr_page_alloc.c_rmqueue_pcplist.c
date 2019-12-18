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
struct zone {int /*<<< orphan*/  pageset; } ;
struct per_cpu_pages {struct list_head* lists; } ;
struct page {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct per_cpu_pages pcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGALLOC ; 
 int /*<<< orphan*/  __count_zid_vm_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct page* __rmqueue_pcplist (struct zone*,int,unsigned int,struct per_cpu_pages*,struct list_head*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  page_zonenum (struct page*) ; 
 TYPE_1__* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_statistics (struct zone*,struct zone*) ; 

__attribute__((used)) static struct page *rmqueue_pcplist(struct zone *preferred_zone,
			struct zone *zone, gfp_t gfp_flags,
			int migratetype, unsigned int alloc_flags)
{
	struct per_cpu_pages *pcp;
	struct list_head *list;
	struct page *page;
	unsigned long flags;

	local_irq_save(flags);
	pcp = &this_cpu_ptr(zone->pageset)->pcp;
	list = &pcp->lists[migratetype];
	page = __rmqueue_pcplist(zone,  migratetype, alloc_flags, pcp, list);
	if (page) {
		__count_zid_vm_events(PGALLOC, page_zonenum(page), 1);
		zone_statistics(preferred_zone, zone);
	}
	local_irq_restore(flags);
	return page;
}