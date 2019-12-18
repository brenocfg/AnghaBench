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
 int RADIX_TREE_MAX_TAGS ; 
 int /*<<< orphan*/  dma_active_cacheline ; 
 scalar_t__ radix_tree_tag_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int active_cacheline_read_overlap(phys_addr_t cln)
{
	int overlap = 0, i;

	for (i = RADIX_TREE_MAX_TAGS - 1; i >= 0; i--)
		if (radix_tree_tag_get(&dma_active_cacheline, cln, i))
			overlap |= 1 << i;
	return overlap;
}