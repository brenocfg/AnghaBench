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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_primary_affinity(struct ceph_osdmap *map, int osd, u32 aff)
{
	BUG_ON(osd >= map->max_osd);

	if (!map->osd_primary_affinity) {
		int i;

		map->osd_primary_affinity = kmalloc_array(map->max_osd,
							  sizeof(u32),
							  GFP_NOFS);
		if (!map->osd_primary_affinity)
			return -ENOMEM;

		for (i = 0; i < map->max_osd; i++)
			map->osd_primary_affinity[i] =
			    CEPH_OSD_DEFAULT_PRIMARY_AFFINITY;
	}

	map->osd_primary_affinity[osd] = aff;

	return 0;
}