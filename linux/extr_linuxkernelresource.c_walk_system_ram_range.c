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
typedef  int u64 ;
struct resource {int start; int end; int flags; } ;

/* Variables and functions */
 int IORESOURCE_BUSY ; 
 int IORESOURCE_SYSTEM_RAM ; 
 int /*<<< orphan*/  IORES_DESC_NONE ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ find_next_iomem_res (struct resource*,int /*<<< orphan*/ ,int) ; 
 int stub1 (unsigned long,unsigned long,void*) ; 

int walk_system_ram_range(unsigned long start_pfn, unsigned long nr_pages,
		void *arg, int (*func)(unsigned long, unsigned long, void *))
{
	struct resource res;
	unsigned long pfn, end_pfn;
	u64 orig_end;
	int ret = -1;

	res.start = (u64) start_pfn << PAGE_SHIFT;
	res.end = ((u64)(start_pfn + nr_pages) << PAGE_SHIFT) - 1;
	res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
	orig_end = res.end;
	while ((res.start < res.end) &&
		(find_next_iomem_res(&res, IORES_DESC_NONE, true) >= 0)) {
		pfn = (res.start + PAGE_SIZE - 1) >> PAGE_SHIFT;
		end_pfn = (res.end + 1) >> PAGE_SHIFT;
		if (end_pfn > pfn)
			ret = (*func)(pfn, end_pfn - pfn, arg);
		if (ret)
			break;
		res.start = res.end + 1;
		res.end = orig_end;
	}
	return ret;
}