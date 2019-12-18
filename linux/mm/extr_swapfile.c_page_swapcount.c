#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_info_struct {int /*<<< orphan*/ * swap_map; } ;
struct swap_cluster_info {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 struct swap_info_struct* _swap_info_get (TYPE_1__) ; 
 struct swap_cluster_info* lock_cluster_or_swap_info (struct swap_info_struct*,unsigned long) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int swap_count (int /*<<< orphan*/ ) ; 
 unsigned long swp_offset (TYPE_1__) ; 
 int /*<<< orphan*/  unlock_cluster_or_swap_info (struct swap_info_struct*,struct swap_cluster_info*) ; 

int page_swapcount(struct page *page)
{
	int count = 0;
	struct swap_info_struct *p;
	struct swap_cluster_info *ci;
	swp_entry_t entry;
	unsigned long offset;

	entry.val = page_private(page);
	p = _swap_info_get(entry);
	if (p) {
		offset = swp_offset(entry);
		ci = lock_cluster_or_swap_info(p, offset);
		count = swap_count(p->swap_map[offset]);
		unlock_cluster_or_swap_info(p, ci);
	}
	return count;
}