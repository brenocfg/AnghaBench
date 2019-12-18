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
typedef  int /*<<< orphan*/  uint64_t ;
struct hmm_range {int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 size_t HMM_PFN_NONE ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static void hmm_pfns_clear(struct hmm_range *range,
			   uint64_t *pfns,
			   unsigned long addr,
			   unsigned long end)
{
	for (; addr < end; addr += PAGE_SIZE, pfns++)
		*pfns = range->values[HMM_PFN_NONE];
}