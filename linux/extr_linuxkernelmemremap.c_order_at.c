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
struct resource {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 unsigned long PHYS_PFN (int /*<<< orphan*/ ) ; 
 unsigned long ULONG_MAX ; 
 unsigned long find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 unsigned long rounddown_pow_of_two (unsigned long) ; 

__attribute__((used)) static unsigned long order_at(struct resource *res, unsigned long pgoff)
{
	unsigned long phys_pgoff = PHYS_PFN(res->start) + pgoff;
	unsigned long nr_pages, mask;

	nr_pages = PHYS_PFN(resource_size(res));
	if (nr_pages == pgoff)
		return ULONG_MAX;

	/*
	 * What is the largest aligned power-of-2 range available from
	 * this resource pgoff to the end of the resource range,
	 * considering the alignment of the current pgoff?
	 */
	mask = phys_pgoff | rounddown_pow_of_two(nr_pages - pgoff);
	if (!mask)
		return ULONG_MAX;

	return find_first_bit(&mask, BITS_PER_LONG);
}