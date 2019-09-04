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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_pg_pool_info {int /*<<< orphan*/  id; } ;
struct ceph_osdmap {int /*<<< orphan*/  pg_pools; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int __insert_pg_pool (int /*<<< orphan*/ *,struct ceph_pg_pool_info*) ; 
 struct ceph_pg_pool_info* __lookup_pg_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_64_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_pool (void**,void*,struct ceph_pg_pool_info*) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  kfree (struct ceph_pg_pool_info*) ; 
 struct ceph_pg_pool_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __decode_pools(void **p, void *end, struct ceph_osdmap *map,
			  bool incremental)
{
	u32 n;

	ceph_decode_32_safe(p, end, n, e_inval);
	while (n--) {
		struct ceph_pg_pool_info *pi;
		u64 pool;
		int ret;

		ceph_decode_64_safe(p, end, pool, e_inval);

		pi = __lookup_pg_pool(&map->pg_pools, pool);
		if (!incremental || !pi) {
			pi = kzalloc(sizeof(*pi), GFP_NOFS);
			if (!pi)
				return -ENOMEM;

			pi->id = pool;

			ret = __insert_pg_pool(&map->pg_pools, pi);
			if (ret) {
				kfree(pi);
				return ret;
			}
		}

		ret = decode_pool(p, end, pi);
		if (ret)
			return ret;
	}

	return 0;

e_inval:
	return -EINVAL;
}