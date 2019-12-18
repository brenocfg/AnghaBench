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
struct vm_struct {int nr_pages; struct page** pages; } ;

/* Variables and functions */
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static inline void set_area_direct_map(const struct vm_struct *area,
				       int (*set_direct_map)(struct page *page))
{
	int i;

	for (i = 0; i < area->nr_pages; i++)
		if (page_address(area->pages[i]))
			set_direct_map(area->pages[i]);
}