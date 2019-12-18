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
struct ceph_pg {int dummy; } ;
struct ceph_osdmap {int dummy; } ;
struct ceph_object_locator {int /*<<< orphan*/  pool; } ;
struct ceph_object_id {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __ceph_object_locator_to_pg (struct ceph_pg_pool_info*,struct ceph_object_id const*,struct ceph_object_locator const*,struct ceph_pg*) ; 
 struct ceph_pg_pool_info* ceph_pg_pool_by_id (struct ceph_osdmap*,int /*<<< orphan*/ ) ; 

int ceph_object_locator_to_pg(struct ceph_osdmap *osdmap,
			      const struct ceph_object_id *oid,
			      const struct ceph_object_locator *oloc,
			      struct ceph_pg *raw_pgid)
{
	struct ceph_pg_pool_info *pi;

	pi = ceph_pg_pool_by_id(osdmap, oloc->pool);
	if (!pi)
		return -ENOENT;

	__ceph_object_locator_to_pg(pi, oid, oloc, raw_pgid);
	return 0;
}