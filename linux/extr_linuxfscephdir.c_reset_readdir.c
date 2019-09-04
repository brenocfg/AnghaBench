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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ceph_dir_file_info {int readdir_cache_idx; int next_offset; TYPE_1__ file_info; scalar_t__ dir_release_count; int /*<<< orphan*/ * last_name; int /*<<< orphan*/ * last_readdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_F_ATEND ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_readdir(struct ceph_dir_file_info *dfi)
{
	if (dfi->last_readdir) {
		ceph_mdsc_put_request(dfi->last_readdir);
		dfi->last_readdir = NULL;
	}
	kfree(dfi->last_name);
	dfi->last_name = NULL;
	dfi->dir_release_count = 0;
	dfi->readdir_cache_idx = -1;
	dfi->next_offset = 2;  /* compensate for . and .. */
	dfi->file_info.flags &= ~CEPH_F_ATEND;
}