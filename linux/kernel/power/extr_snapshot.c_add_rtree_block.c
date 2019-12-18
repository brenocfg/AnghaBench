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
struct rtree_node {unsigned long* data; } ;
struct mem_zone_bm_rtree {unsigned int blocks; int levels; int /*<<< orphan*/  nodes; struct rtree_node* rtree; int /*<<< orphan*/  leaves; } ;
struct chain_allocator {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int BM_RTREE_LEVEL_MASK ; 
 unsigned int BM_RTREE_LEVEL_SHIFT ; 
 int ENOMEM ; 
 struct rtree_node* alloc_rtree_node (int /*<<< orphan*/ ,int,struct chain_allocator*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_rtree_block(struct mem_zone_bm_rtree *zone, gfp_t gfp_mask,
			   int safe_needed, struct chain_allocator *ca)
{
	struct rtree_node *node, *block, **dst;
	unsigned int levels_needed, block_nr;
	int i;

	block_nr = zone->blocks;
	levels_needed = 0;

	/* How many levels do we need for this block nr? */
	while (block_nr) {
		levels_needed += 1;
		block_nr >>= BM_RTREE_LEVEL_SHIFT;
	}

	/* Make sure the rtree has enough levels */
	for (i = zone->levels; i < levels_needed; i++) {
		node = alloc_rtree_node(gfp_mask, safe_needed, ca,
					&zone->nodes);
		if (!node)
			return -ENOMEM;

		node->data[0] = (unsigned long)zone->rtree;
		zone->rtree = node;
		zone->levels += 1;
	}

	/* Allocate new block */
	block = alloc_rtree_node(gfp_mask, safe_needed, ca, &zone->leaves);
	if (!block)
		return -ENOMEM;

	/* Now walk the rtree to insert the block */
	node = zone->rtree;
	dst = &zone->rtree;
	block_nr = zone->blocks;
	for (i = zone->levels; i > 0; i--) {
		int index;

		if (!node) {
			node = alloc_rtree_node(gfp_mask, safe_needed, ca,
						&zone->nodes);
			if (!node)
				return -ENOMEM;
			*dst = node;
		}

		index = block_nr >> ((i - 1) * BM_RTREE_LEVEL_SHIFT);
		index &= BM_RTREE_LEVEL_MASK;
		dst = (struct rtree_node **)&((*dst)->data[index]);
		node = *dst;
	}

	zone->blocks += 1;
	*dst = block;

	return 0;
}