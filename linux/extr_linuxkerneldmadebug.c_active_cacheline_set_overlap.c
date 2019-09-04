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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ACTIVE_CACHELINE_MAX_OVERLAP ; 
 int RADIX_TREE_MAX_TAGS ; 
 int /*<<< orphan*/  dma_active_cacheline ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int active_cacheline_set_overlap(phys_addr_t cln, int overlap)
{
	int i;

	if (overlap > ACTIVE_CACHELINE_MAX_OVERLAP || overlap < 0)
		return overlap;

	for (i = RADIX_TREE_MAX_TAGS - 1; i >= 0; i--)
		if (overlap & 1 << i)
			radix_tree_tag_set(&dma_active_cacheline, cln, i);
		else
			radix_tree_tag_clear(&dma_active_cacheline, cln, i);

	return overlap;
}