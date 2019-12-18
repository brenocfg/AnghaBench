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
struct zone {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 unsigned int ALLOC_KSWAPD ; 
 unsigned int ALLOC_NOFRAGMENT ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ ZONE_DMA32 ; 
 scalar_t__ ZONE_NORMAL ; 
 int __GFP_KSWAPD_RECLAIM ; 
 int nr_online_nodes ; 
 int /*<<< orphan*/  populated_zone (struct zone*) ; 
 scalar_t__ zone_idx (struct zone*) ; 

__attribute__((used)) static inline unsigned int
alloc_flags_nofragment(struct zone *zone, gfp_t gfp_mask)
{
	unsigned int alloc_flags = 0;

	if (gfp_mask & __GFP_KSWAPD_RECLAIM)
		alloc_flags |= ALLOC_KSWAPD;

#ifdef CONFIG_ZONE_DMA32
	if (!zone)
		return alloc_flags;

	if (zone_idx(zone) != ZONE_NORMAL)
		return alloc_flags;

	/*
	 * If ZONE_DMA32 exists, assume it is the one after ZONE_NORMAL and
	 * the pointer is within zone->zone_pgdat->node_zones[]. Also assume
	 * on UMA that if Normal is populated then so is DMA32.
	 */
	BUILD_BUG_ON(ZONE_NORMAL - ZONE_DMA32 != 1);
	if (nr_online_nodes > 1 && !populated_zone(--zone))
		return alloc_flags;

	alloc_flags |= ALLOC_NOFRAGMENT;
#endif /* CONFIG_ZONE_DMA32 */
	return alloc_flags;
}