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
struct super_block {int dummy; } ;
struct ceph_options {int flags; int /*<<< orphan*/  fsid; } ;
struct ceph_mount_options {scalar_t__ sb_flags; } ;
struct ceph_fs_client {struct ceph_mount_options* mount_options; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  fsid; struct ceph_options* options; } ;

/* Variables and functions */
 int CEPH_OPT_FSID ; 
 scalar_t__ ceph_fsid_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ceph_fs_client* ceph_sb_to_client (struct super_block*) ; 
 scalar_t__ compare_mount_options (struct ceph_mount_options*,struct ceph_options*,struct ceph_fs_client*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 

__attribute__((used)) static int ceph_compare_super(struct super_block *sb, void *data)
{
	struct ceph_fs_client *new = data;
	struct ceph_mount_options *fsopt = new->mount_options;
	struct ceph_options *opt = new->client->options;
	struct ceph_fs_client *other = ceph_sb_to_client(sb);

	dout("ceph_compare_super %p\n", sb);

	if (compare_mount_options(fsopt, opt, other)) {
		dout("monitor(s)/mount options don't match\n");
		return 0;
	}
	if ((opt->flags & CEPH_OPT_FSID) &&
	    ceph_fsid_compare(&opt->fsid, &other->client->fsid)) {
		dout("fsid doesn't match\n");
		return 0;
	}
	if (fsopt->sb_flags != other->mount_options->sb_flags) {
		dout("flags differ\n");
		return 0;
	}
	return 1;
}