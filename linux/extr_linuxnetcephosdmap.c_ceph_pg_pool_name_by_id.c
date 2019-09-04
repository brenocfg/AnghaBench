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
typedef  scalar_t__ u64 ;
struct ceph_pg_pool_info {char const* name; } ;
struct ceph_osdmap {int /*<<< orphan*/  pg_pools; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOPOOL ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct ceph_pg_pool_info* __lookup_pg_pool (int /*<<< orphan*/ *,int) ; 

const char *ceph_pg_pool_name_by_id(struct ceph_osdmap *map, u64 id)
{
	struct ceph_pg_pool_info *pi;

	if (id == CEPH_NOPOOL)
		return NULL;

	if (WARN_ON_ONCE(id > (u64) INT_MAX))
		return NULL;

	pi = __lookup_pg_pool(&map->pg_pools, (int) id);

	return pi ? pi->name : NULL;
}