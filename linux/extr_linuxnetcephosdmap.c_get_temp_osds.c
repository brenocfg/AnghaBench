#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ceph_pg_pool_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ osd; } ;
struct TYPE_3__ {int len; scalar_t__* osds; } ;
struct ceph_pg_mapping {TYPE_2__ primary_temp; TYPE_1__ pg_temp; } ;
struct ceph_pg {int dummy; } ;
struct ceph_osds {scalar_t__* osds; int size; scalar_t__ primary; } ;
struct ceph_osdmap {int /*<<< orphan*/  primary_temp; int /*<<< orphan*/  pg_temp; } ;

/* Variables and functions */
 scalar_t__ CRUSH_ITEM_NONE ; 
 scalar_t__ ceph_can_shift_osds (struct ceph_pg_pool_info*) ; 
 scalar_t__ ceph_osd_is_down (struct ceph_osdmap*,scalar_t__) ; 
 int /*<<< orphan*/  ceph_osds_init (struct ceph_osds*) ; 
 struct ceph_pg_mapping* lookup_pg_mapping (int /*<<< orphan*/ *,struct ceph_pg const*) ; 

__attribute__((used)) static void get_temp_osds(struct ceph_osdmap *osdmap,
			  struct ceph_pg_pool_info *pi,
			  const struct ceph_pg *pgid,
			  struct ceph_osds *temp)
{
	struct ceph_pg_mapping *pg;
	int i;

	ceph_osds_init(temp);

	/* pg_temp? */
	pg = lookup_pg_mapping(&osdmap->pg_temp, pgid);
	if (pg) {
		for (i = 0; i < pg->pg_temp.len; i++) {
			if (ceph_osd_is_down(osdmap, pg->pg_temp.osds[i])) {
				if (ceph_can_shift_osds(pi))
					continue;

				temp->osds[temp->size++] = CRUSH_ITEM_NONE;
			} else {
				temp->osds[temp->size++] = pg->pg_temp.osds[i];
			}
		}

		/* apply pg_temp's primary */
		for (i = 0; i < temp->size; i++) {
			if (temp->osds[i] != CRUSH_ITEM_NONE) {
				temp->primary = temp->osds[i];
				break;
			}
		}
	}

	/* primary_temp? */
	pg = lookup_pg_mapping(&osdmap->primary_temp, pgid);
	if (pg)
		temp->primary = pg->primary_temp.osd;
}