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
typedef  unsigned int u32 ;
struct ceph_pg_pool_info {int flags; int /*<<< orphan*/  pgp_num_mask; int /*<<< orphan*/  pgp_num; } ;
struct ceph_pg {scalar_t__ pool; int /*<<< orphan*/  seed; } ;

/* Variables and functions */
 int CEPH_POOL_FLAG_HASHPSPOOL ; 
 int /*<<< orphan*/  CRUSH_HASH_RJENKINS1 ; 
 unsigned int ceph_stable_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crush_hash32_2 (int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 

__attribute__((used)) static u32 raw_pg_to_pps(struct ceph_pg_pool_info *pi,
			 const struct ceph_pg *raw_pgid)
{
	if (pi->flags & CEPH_POOL_FLAG_HASHPSPOOL) {
		/* hash pool id and seed so that pool PGs do not overlap */
		return crush_hash32_2(CRUSH_HASH_RJENKINS1,
				      ceph_stable_mod(raw_pgid->seed,
						      pi->pgp_num,
						      pi->pgp_num_mask),
				      raw_pgid->pool);
	} else {
		/*
		 * legacy behavior: add ps and pool together.  this is
		 * not a great approach because the PGs from each pool
		 * will overlap on top of each other: 0.5 == 1.4 ==
		 * 2.3 == ...
		 */
		return ceph_stable_mod(raw_pgid->seed, pi->pgp_num,
				       pi->pgp_num_mask) +
		       (unsigned)raw_pgid->pool;
	}
}