#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zone {int dummy; } ;
struct TYPE_3__ {struct zone* node_zones; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 unsigned long high_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  managed_zone (struct zone*) ; 
 scalar_t__ zone_watermark_ok_safe (struct zone*,int,unsigned long,int) ; 

__attribute__((used)) static bool pgdat_balanced(pg_data_t *pgdat, int order, int classzone_idx)
{
	int i;
	unsigned long mark = -1;
	struct zone *zone;

	/*
	 * Check watermarks bottom-up as lower zones are more likely to
	 * meet watermarks.
	 */
	for (i = 0; i <= classzone_idx; i++) {
		zone = pgdat->node_zones + i;

		if (!managed_zone(zone))
			continue;

		mark = high_wmark_pages(zone);
		if (zone_watermark_ok_safe(zone, order, mark, classzone_idx))
			return true;
	}

	/*
	 * If a node has no populated zone within classzone_idx, it does not
	 * need balancing by definition. This can happen if a zone-restricted
	 * allocation tries to wake a remote kswapd.
	 */
	if (mark == -1)
		return true;

	return false;
}