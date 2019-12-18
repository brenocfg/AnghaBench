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
struct ceph_pg {int dummy; } ;
struct ceph_osds {int dummy; } ;

/* Variables and functions */
 scalar_t__ ceph_pg_is_split (struct ceph_pg const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osds_equal (struct ceph_osds const*,struct ceph_osds const*) ; 

bool ceph_is_new_interval(const struct ceph_osds *old_acting,
			  const struct ceph_osds *new_acting,
			  const struct ceph_osds *old_up,
			  const struct ceph_osds *new_up,
			  int old_size,
			  int new_size,
			  int old_min_size,
			  int new_min_size,
			  u32 old_pg_num,
			  u32 new_pg_num,
			  bool old_sort_bitwise,
			  bool new_sort_bitwise,
			  bool old_recovery_deletes,
			  bool new_recovery_deletes,
			  const struct ceph_pg *pgid)
{
	return !osds_equal(old_acting, new_acting) ||
	       !osds_equal(old_up, new_up) ||
	       old_size != new_size ||
	       old_min_size != new_min_size ||
	       ceph_pg_is_split(pgid, old_pg_num, new_pg_num) ||
	       old_sort_bitwise != new_sort_bitwise ||
	       old_recovery_deletes != new_recovery_deletes;
}