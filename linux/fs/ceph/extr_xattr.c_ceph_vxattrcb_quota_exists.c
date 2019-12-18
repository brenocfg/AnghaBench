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
struct TYPE_3__ {scalar_t__ snap; scalar_t__ ino; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; TYPE_1__ i_vino; TYPE_2__* i_snap_realm; scalar_t__ i_max_bytes; scalar_t__ i_max_files; } ;
struct TYPE_4__ {scalar_t__ ino; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ceph_vxattrcb_quota_exists(struct ceph_inode_info *ci)
{
	bool ret = false;
	spin_lock(&ci->i_ceph_lock);
	if ((ci->i_max_files || ci->i_max_bytes) &&
	    ci->i_vino.snap == CEPH_NOSNAP &&
	    ci->i_snap_realm &&
	    ci->i_snap_realm->ino == ci->i_vino.ino)
		ret = true;
	spin_unlock(&ci->i_ceph_lock);
	return ret;
}