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
struct vm_struct {int flags; int nr_pages; int /*<<< orphan*/ * pages; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 unsigned long ULONG_MAX ; 
 int VM_FLUSH_RESET_PERMS ; 
 int /*<<< orphan*/  _vm_unmap_aliases (unsigned long,unsigned long,int) ; 
 unsigned long max (scalar_t__,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_vm_area (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_area_direct_map (struct vm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_direct_map_default_noflush ; 
 int /*<<< orphan*/  set_direct_map_invalid_noflush ; 
 int /*<<< orphan*/  vm_unmap_aliases () ; 

__attribute__((used)) static void vm_remove_mappings(struct vm_struct *area, int deallocate_pages)
{
	unsigned long start = ULONG_MAX, end = 0;
	int flush_reset = area->flags & VM_FLUSH_RESET_PERMS;
	int flush_dmap = 0;
	int i;

	remove_vm_area(area->addr);

	/* If this is not VM_FLUSH_RESET_PERMS memory, no need for the below. */
	if (!flush_reset)
		return;

	/*
	 * If not deallocating pages, just do the flush of the VM area and
	 * return.
	 */
	if (!deallocate_pages) {
		vm_unmap_aliases();
		return;
	}

	/*
	 * If execution gets here, flush the vm mapping and reset the direct
	 * map. Find the start and end range of the direct mappings to make sure
	 * the vm_unmap_aliases() flush includes the direct map.
	 */
	for (i = 0; i < area->nr_pages; i++) {
		unsigned long addr = (unsigned long)page_address(area->pages[i]);
		if (addr) {
			start = min(addr, start);
			end = max(addr + PAGE_SIZE, end);
			flush_dmap = 1;
		}
	}

	/*
	 * Set direct map to something invalid so that it won't be cached if
	 * there are any accesses after the TLB flush, then flush the TLB and
	 * reset the direct map permissions to the default.
	 */
	set_area_direct_map(area, set_direct_map_invalid_noflush);
	_vm_unmap_aliases(start, end, flush_dmap);
	set_area_direct_map(area, set_direct_map_default_noflush);
}