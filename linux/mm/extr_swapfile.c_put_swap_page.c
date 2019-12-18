#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_info_struct {unsigned char* swap_map; int /*<<< orphan*/  lock; } ;
struct swap_cluster_info {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long SWAPFILE_CLUSTER ; 
 unsigned char SWAP_HAS_CACHE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __swap_entry_free_locked (struct swap_info_struct*,unsigned long,unsigned char) ; 
 struct swap_info_struct* _swap_info_get (TYPE_1__) ; 
 int /*<<< orphan*/  cluster_clear_huge (struct swap_cluster_info*) ; 
 int /*<<< orphan*/  cluster_is_huge (struct swap_cluster_info*) ; 
 int /*<<< orphan*/  free_swap_slot (TYPE_1__) ; 
 int /*<<< orphan*/  hpage_nr_pages (struct page*) ; 
 struct swap_cluster_info* lock_cluster_or_swap_info (struct swap_info_struct*,unsigned long) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_swap (TYPE_1__,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int swap_entry_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_free_cluster (struct swap_info_struct*,unsigned long) ; 
 unsigned long swp_offset (TYPE_1__) ; 
 int /*<<< orphan*/  unlock_cluster_or_swap_info (struct swap_info_struct*,struct swap_cluster_info*) ; 

void put_swap_page(struct page *page, swp_entry_t entry)
{
	unsigned long offset = swp_offset(entry);
	unsigned long idx = offset / SWAPFILE_CLUSTER;
	struct swap_cluster_info *ci;
	struct swap_info_struct *si;
	unsigned char *map;
	unsigned int i, free_entries = 0;
	unsigned char val;
	int size = swap_entry_size(hpage_nr_pages(page));

	si = _swap_info_get(entry);
	if (!si)
		return;

	ci = lock_cluster_or_swap_info(si, offset);
	if (size == SWAPFILE_CLUSTER) {
		VM_BUG_ON(!cluster_is_huge(ci));
		map = si->swap_map + offset;
		for (i = 0; i < SWAPFILE_CLUSTER; i++) {
			val = map[i];
			VM_BUG_ON(!(val & SWAP_HAS_CACHE));
			if (val == SWAP_HAS_CACHE)
				free_entries++;
		}
		cluster_clear_huge(ci);
		if (free_entries == SWAPFILE_CLUSTER) {
			unlock_cluster_or_swap_info(si, ci);
			spin_lock(&si->lock);
			mem_cgroup_uncharge_swap(entry, SWAPFILE_CLUSTER);
			swap_free_cluster(si, idx);
			spin_unlock(&si->lock);
			return;
		}
	}
	for (i = 0; i < size; i++, entry.val++) {
		if (!__swap_entry_free_locked(si, offset + i, SWAP_HAS_CACHE)) {
			unlock_cluster_or_swap_info(si, ci);
			free_swap_slot(entry);
			if (i == size - 1)
				return;
			lock_cluster_or_swap_info(si, offset);
		}
	}
	unlock_cluster_or_swap_info(si, ci);
}