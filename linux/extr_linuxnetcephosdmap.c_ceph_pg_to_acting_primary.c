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
struct ceph_pg {int /*<<< orphan*/  pool; } ;
struct ceph_osds {int primary; } ;
struct ceph_osdmap {int dummy; } ;

/* Variables and functions */
 struct ceph_pg_pool_info* ceph_pg_pool_by_id (struct ceph_osdmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_pg_to_up_acting_osds (struct ceph_osdmap*,struct ceph_pg_pool_info*,struct ceph_pg const*,struct ceph_osds*,struct ceph_osds*) ; 

int ceph_pg_to_acting_primary(struct ceph_osdmap *osdmap,
			      const struct ceph_pg *raw_pgid)
{
	struct ceph_pg_pool_info *pi;
	struct ceph_osds up, acting;

	pi = ceph_pg_pool_by_id(osdmap, raw_pgid->pool);
	if (!pi)
		return -1;

	ceph_pg_to_up_acting_osds(osdmap, pi, raw_pgid, &up, &acting);
	return acting.primary;
}