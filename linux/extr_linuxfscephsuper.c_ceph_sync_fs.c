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
struct ceph_fs_client {int /*<<< orphan*/  mdsc; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_flush_dirty_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_mdsc_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_sync (int /*<<< orphan*/ *) ; 
 struct ceph_fs_client* ceph_sb_to_client (struct super_block*) ; 
 int /*<<< orphan*/  dout (char*) ; 

__attribute__((used)) static int ceph_sync_fs(struct super_block *sb, int wait)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(sb);

	if (!wait) {
		dout("sync_fs (non-blocking)\n");
		ceph_flush_dirty_caps(fsc->mdsc);
		dout("sync_fs (non-blocking) done\n");
		return 0;
	}

	dout("sync_fs (blocking)\n");
	ceph_osdc_sync(&fsc->client->osdc);
	ceph_mdsc_sync(fsc->mdsc);
	dout("sync_fs (blocking) done\n");
	return 0;
}