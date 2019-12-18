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
struct super_block {int /*<<< orphan*/  s_dev; } ;
struct ceph_fs_client {TYPE_1__* client; int /*<<< orphan*/  mdsc; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/ * extra_mon_dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_fs_debugfs_cleanup (struct ceph_fs_client*) ; 
 int /*<<< orphan*/  ceph_fscache_unregister_fs (struct ceph_fs_client*) ; 
 int /*<<< orphan*/  ceph_mdsc_pre_umount (int /*<<< orphan*/ ) ; 
 struct ceph_fs_client* ceph_sb_to_client (struct super_block*) ; 
 int /*<<< orphan*/  destroy_fs_client (struct ceph_fs_client*) ; 
 int /*<<< orphan*/  dout (char*,struct super_block*) ; 
 int /*<<< orphan*/  flush_fs_workqueues (struct ceph_fs_client*) ; 
 int /*<<< orphan*/  free_anon_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_shutdown_super (struct super_block*) ; 

__attribute__((used)) static void ceph_kill_sb(struct super_block *s)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(s);
	dev_t dev = s->s_dev;

	dout("kill_sb %p\n", s);

	ceph_mdsc_pre_umount(fsc->mdsc);
	flush_fs_workqueues(fsc);

	generic_shutdown_super(s);

	fsc->client->extra_mon_dispatch = NULL;
	ceph_fs_debugfs_cleanup(fsc);

	ceph_fscache_unregister_fs(fsc);

	destroy_fs_client(fsc);
	free_anon_bdev(dev);
}