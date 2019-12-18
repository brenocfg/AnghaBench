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
struct ceph_pg_pool_info {int /*<<< orphan*/  pg_num_mask; int /*<<< orphan*/  pg_num; } ;
struct ceph_pg {int /*<<< orphan*/  seed; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_stable_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raw_pg_to_pg(struct ceph_pg_pool_info *pi,
			 const struct ceph_pg *raw_pgid,
			 struct ceph_pg *pgid)
{
	pgid->pool = raw_pgid->pool;
	pgid->seed = ceph_stable_mod(raw_pgid->seed, pi->pg_num,
				     pi->pg_num_mask);
}