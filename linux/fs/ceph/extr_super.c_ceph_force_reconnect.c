#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {scalar_t__ s_root; } ;
struct ceph_fs_client {int blacklisted; int /*<<< orphan*/  mount_state; TYPE_1__* client; int /*<<< orphan*/  inode_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MOUNT_MOUNTED ; 
 int /*<<< orphan*/  CEPH_STAT_CAP_INODE ; 
 int __ceph_do_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_osdc_clear_abort_err (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_reset_client_addr (TYPE_1__*) ; 
 struct ceph_fs_client* ceph_sb_to_client (struct super_block*) ; 
 int /*<<< orphan*/  ceph_umount_begin (struct super_block*) ; 
 int /*<<< orphan*/  d_inode (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

int ceph_force_reconnect(struct super_block *sb)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(sb);
	int err = 0;

	ceph_umount_begin(sb);

	/* Make sure all page caches get invalidated.
	 * see remove_session_caps_cb() */
	flush_workqueue(fsc->inode_wq);

	/* In case that we were blacklisted. This also reset
	 * all mon/osd connections */
	ceph_reset_client_addr(fsc->client);

	ceph_osdc_clear_abort_err(&fsc->client->osdc);

	fsc->blacklisted = false;
	fsc->mount_state = CEPH_MOUNT_MOUNTED;

	if (sb->s_root) {
		err = __ceph_do_getattr(d_inode(sb->s_root), NULL,
					CEPH_STAT_CAP_INODE, true);
	}
	return err;
}