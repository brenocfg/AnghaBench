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
struct kvm_memory_slot {size_t npages; unsigned long base_gfn; size_t userspace_addr; } ;
typedef  size_t hva_t ;
typedef  unsigned long gpa_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 

__attribute__((used)) static bool fault_supports_stage2_huge_mapping(struct kvm_memory_slot *memslot,
					       unsigned long hva,
					       unsigned long map_size)
{
	gpa_t gpa_start;
	hva_t uaddr_start, uaddr_end;
	size_t size;

	size = memslot->npages * PAGE_SIZE;

	gpa_start = memslot->base_gfn << PAGE_SHIFT;

	uaddr_start = memslot->userspace_addr;
	uaddr_end = uaddr_start + size;

	/*
	 * Pages belonging to memslots that don't have the same alignment
	 * within a PMD/PUD for userspace and IPA cannot be mapped with stage-2
	 * PMD/PUD entries, because we'll end up mapping the wrong pages.
	 *
	 * Consider a layout like the following:
	 *
	 *    memslot->userspace_addr:
	 *    +-----+--------------------+--------------------+---+
	 *    |abcde|fgh  Stage-1 block  |    Stage-1 block tv|xyz|
	 *    +-----+--------------------+--------------------+---+
	 *
	 *    memslot->base_gfn << PAGE_SIZE:
	 *      +---+--------------------+--------------------+-----+
	 *      |abc|def  Stage-2 block  |    Stage-2 block   |tvxyz|
	 *      +---+--------------------+--------------------+-----+
	 *
	 * If we create those stage-2 blocks, we'll end up with this incorrect
	 * mapping:
	 *   d -> f
	 *   e -> g
	 *   f -> h
	 */
	if ((gpa_start & (map_size - 1)) != (uaddr_start & (map_size - 1)))
		return false;

	/*
	 * Next, let's make sure we're not trying to map anything not covered
	 * by the memslot. This means we have to prohibit block size mappings
	 * for the beginning and end of a non-block aligned and non-block sized
	 * memory slot (illustrated by the head and tail parts of the
	 * userspace view above containing pages 'abcde' and 'xyz',
	 * respectively).
	 *
	 * Note that it doesn't matter if we do the check using the
	 * userspace_addr or the base_gfn, as both are equally aligned (per
	 * the check above) and equally sized.
	 */
	return (hva & ~(map_size - 1)) >= uaddr_start &&
	       (hva & ~(map_size - 1)) + map_size <= uaddr_end;
}