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
struct mem_zone_bm_rtree {unsigned long start_pfn; unsigned long end_pfn; int /*<<< orphan*/  leaves; int /*<<< orphan*/  nodes; } ;
struct chain_allocator {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BM_BITS_PER_BLOCK ; 
 unsigned int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PG_UNSAFE_CLEAR ; 
 scalar_t__ add_rtree_block (struct mem_zone_bm_rtree*,int /*<<< orphan*/ ,int,struct chain_allocator*) ; 
 struct mem_zone_bm_rtree* chain_alloc (struct chain_allocator*,int) ; 
 int /*<<< orphan*/  free_zone_bm_rtree (struct mem_zone_bm_rtree*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mem_zone_bm_rtree *create_zone_bm_rtree(gfp_t gfp_mask,
						      int safe_needed,
						      struct chain_allocator *ca,
						      unsigned long start,
						      unsigned long end)
{
	struct mem_zone_bm_rtree *zone;
	unsigned int i, nr_blocks;
	unsigned long pages;

	pages = end - start;
	zone  = chain_alloc(ca, sizeof(struct mem_zone_bm_rtree));
	if (!zone)
		return NULL;

	INIT_LIST_HEAD(&zone->nodes);
	INIT_LIST_HEAD(&zone->leaves);
	zone->start_pfn = start;
	zone->end_pfn = end;
	nr_blocks = DIV_ROUND_UP(pages, BM_BITS_PER_BLOCK);

	for (i = 0; i < nr_blocks; i++) {
		if (add_rtree_block(zone, gfp_mask, safe_needed, ca)) {
			free_zone_bm_rtree(zone, PG_UNSAFE_CLEAR);
			return NULL;
		}
	}

	return zone;
}