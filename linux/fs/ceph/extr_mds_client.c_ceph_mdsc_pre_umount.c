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
struct ceph_mds_client {int stopping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_cleanup_quotarealms_inodes (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  ceph_flush_dirty_caps (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  ceph_msgr_flush () ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  lock_unlock_sessions (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  wait_requests (struct ceph_mds_client*) ; 

void ceph_mdsc_pre_umount(struct ceph_mds_client *mdsc)
{
	dout("pre_umount\n");
	mdsc->stopping = 1;

	lock_unlock_sessions(mdsc);
	ceph_flush_dirty_caps(mdsc);
	wait_requests(mdsc);

	/*
	 * wait for reply handlers to drop their request refs and
	 * their inode/dcache refs
	 */
	ceph_msgr_flush();

	ceph_cleanup_quotarealms_inodes(mdsc);
}