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
typedef  int /*<<< orphan*/  u32 ;
struct ceph_osdmap {int max_osd; int /*<<< orphan*/ * osd_primary_affinity; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_OSD_DEFAULT_PRIMARY_AFFINITY ; 

u32 ceph_get_primary_affinity(struct ceph_osdmap *map, int osd)
{
	BUG_ON(osd >= map->max_osd);

	if (!map->osd_primary_affinity)
		return CEPH_OSD_DEFAULT_PRIMARY_AFFINITY;

	return map->osd_primary_affinity[osd];
}