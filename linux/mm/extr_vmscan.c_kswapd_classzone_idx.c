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
struct TYPE_3__ {scalar_t__ kswapd_classzone_idx; } ;
typedef  TYPE_1__ pg_data_t ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;

/* Variables and functions */
 scalar_t__ MAX_NR_ZONES ; 

__attribute__((used)) static enum zone_type kswapd_classzone_idx(pg_data_t *pgdat,
					   enum zone_type prev_classzone_idx)
{
	if (pgdat->kswapd_classzone_idx == MAX_NR_ZONES)
		return prev_classzone_idx;
	return pgdat->kswapd_classzone_idx;
}