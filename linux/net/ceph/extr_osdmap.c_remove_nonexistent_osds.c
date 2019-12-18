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
struct ceph_pg_pool_info {int dummy; } ;
struct ceph_osds {int size; int /*<<< orphan*/ * osds; } ;
struct ceph_osdmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRUSH_ITEM_NONE ; 
 scalar_t__ ceph_can_shift_osds (struct ceph_pg_pool_info*) ; 
 int /*<<< orphan*/  ceph_osd_exists (struct ceph_osdmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_nonexistent_osds(struct ceph_osdmap *osdmap,
				    struct ceph_pg_pool_info *pi,
				    struct ceph_osds *set)
{
	int i;

	if (ceph_can_shift_osds(pi)) {
		int removed = 0;

		/* shift left */
		for (i = 0; i < set->size; i++) {
			if (!ceph_osd_exists(osdmap, set->osds[i])) {
				removed++;
				continue;
			}
			if (removed)
				set->osds[i - removed] = set->osds[i];
		}
		set->size -= removed;
	} else {
		/* set dne devices to NONE */
		for (i = 0; i < set->size; i++) {
			if (!ceph_osd_exists(osdmap, set->osds[i]))
				set->osds[i] = CRUSH_ITEM_NONE;
		}
	}
}