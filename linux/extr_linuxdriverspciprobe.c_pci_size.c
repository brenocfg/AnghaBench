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

/* Variables and functions */

__attribute__((used)) static u64 pci_size(u64 base, u64 maxbase, u64 mask)
{
	u64 size = mask & maxbase;	/* Find the significant bits */
	if (!size)
		return 0;

	/*
	 * Get the lowest of them to find the decode size, and from that
	 * the extent.
	 */
	size = (size & ~(size-1)) - 1;

	/*
	 * base == maxbase can be valid only if the BAR has already been
	 * programmed with all 1s.
	 */
	if (base == maxbase && ((base | size) & mask) != mask)
		return 0;

	return size;
}