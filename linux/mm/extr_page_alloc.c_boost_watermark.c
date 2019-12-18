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
struct zone {scalar_t__ watermark_boost; int /*<<< orphan*/ * _watermark; } ;

/* Variables and functions */
 size_t WMARK_HIGH ; 
 unsigned long max (scalar_t__,unsigned long) ; 
 scalar_t__ min (scalar_t__,unsigned long) ; 
 unsigned long mult_frac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pageblock_nr_pages ; 
 int /*<<< orphan*/  watermark_boost_factor ; 

__attribute__((used)) static inline void boost_watermark(struct zone *zone)
{
	unsigned long max_boost;

	if (!watermark_boost_factor)
		return;

	max_boost = mult_frac(zone->_watermark[WMARK_HIGH],
			watermark_boost_factor, 10000);

	/*
	 * high watermark may be uninitialised if fragmentation occurs
	 * very early in boot so do not boost. We do not fall
	 * through and boost by pageblock_nr_pages as failing
	 * allocations that early means that reclaim is not going
	 * to help and it may even be impossible to reclaim the
	 * boosted watermark resulting in a hang.
	 */
	if (!max_boost)
		return;

	max_boost = max(pageblock_nr_pages, max_boost);

	zone->watermark_boost = min(zone->watermark_boost + pageblock_nr_pages,
		max_boost);
}