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
struct ceph_file_layout {scalar_t__ stripe_unit; scalar_t__ stripe_count; scalar_t__ object_size; scalar_t__ pool_id; int /*<<< orphan*/  pool_ns; } ;
struct ceph_inode_info {struct ceph_file_layout i_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/ * rcu_dereference_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ceph_vxattrcb_layout_exists(struct ceph_inode_info *ci)
{
	struct ceph_file_layout *fl = &ci->i_layout;
	return (fl->stripe_unit > 0 || fl->stripe_count > 0 ||
		fl->object_size > 0 || fl->pool_id >= 0 ||
		rcu_dereference_raw(fl->pool_ns) != NULL);
}