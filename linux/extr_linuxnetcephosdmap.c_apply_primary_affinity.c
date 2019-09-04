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
typedef  int u32 ;
struct ceph_pg_pool_info {int dummy; } ;
struct ceph_osds {int size; int* osds; int primary; } ;
struct ceph_osdmap {scalar_t__* osd_primary_affinity; } ;

/* Variables and functions */
 scalar_t__ CEPH_OSD_DEFAULT_PRIMARY_AFFINITY ; 
 int CEPH_OSD_MAX_PRIMARY_AFFINITY ; 
 int /*<<< orphan*/  CRUSH_HASH_RJENKINS1 ; 
 int CRUSH_ITEM_NONE ; 
 scalar_t__ ceph_can_shift_osds (struct ceph_pg_pool_info*) ; 
 int crush_hash32_2 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void apply_primary_affinity(struct ceph_osdmap *osdmap,
				   struct ceph_pg_pool_info *pi,
				   u32 pps,
				   struct ceph_osds *up)
{
	int i;
	int pos = -1;

	/*
	 * Do we have any non-default primary_affinity values for these
	 * osds?
	 */
	if (!osdmap->osd_primary_affinity)
		return;

	for (i = 0; i < up->size; i++) {
		int osd = up->osds[i];

		if (osd != CRUSH_ITEM_NONE &&
		    osdmap->osd_primary_affinity[osd] !=
					CEPH_OSD_DEFAULT_PRIMARY_AFFINITY) {
			break;
		}
	}
	if (i == up->size)
		return;

	/*
	 * Pick the primary.  Feed both the seed (for the pg) and the
	 * osd into the hash/rng so that a proportional fraction of an
	 * osd's pgs get rejected as primary.
	 */
	for (i = 0; i < up->size; i++) {
		int osd = up->osds[i];
		u32 aff;

		if (osd == CRUSH_ITEM_NONE)
			continue;

		aff = osdmap->osd_primary_affinity[osd];
		if (aff < CEPH_OSD_MAX_PRIMARY_AFFINITY &&
		    (crush_hash32_2(CRUSH_HASH_RJENKINS1,
				    pps, osd) >> 16) >= aff) {
			/*
			 * We chose not to use this primary.  Note it
			 * anyway as a fallback in case we don't pick
			 * anyone else, but keep looking.
			 */
			if (pos < 0)
				pos = i;
		} else {
			pos = i;
			break;
		}
	}
	if (pos < 0)
		return;

	up->primary = up->osds[pos];

	if (ceph_can_shift_osds(pi) && pos > 0) {
		/* move the new primary to the front */
		for (i = pos; i > 0; i--)
			up->osds[i] = up->osds[i - 1];
		up->osds[0] = up->primary;
	}
}