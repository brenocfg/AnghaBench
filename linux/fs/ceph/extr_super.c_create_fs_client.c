#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct ceph_options {int dummy; } ;
struct ceph_mount_options {int wsize; int /*<<< orphan*/  mds_namespace; } ;
struct ceph_fs_client {int filp_gen; TYPE_1__* client; void* inode_wq; void* cap_wq; int /*<<< orphan*/  wb_pagevec_pool; struct ceph_mount_options* mount_options; int /*<<< orphan*/  writeback_count; int /*<<< orphan*/  mount_state; int /*<<< orphan*/ * sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  monc; int /*<<< orphan*/  extra_mon_dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ON_FULL ; 
 int /*<<< orphan*/  CEPH_MOUNT_MOUNTING ; 
 int /*<<< orphan*/  CEPH_SUB_FSMAP ; 
 int /*<<< orphan*/  CEPH_SUB_MDSMAP ; 
 int ENOMEM ; 
 struct ceph_fs_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 void* alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ceph_create_client (struct ceph_options*,struct ceph_fs_client*) ; 
 int /*<<< orphan*/  ceph_destroy_client (TYPE_1__*) ; 
 int /*<<< orphan*/  ceph_destroy_options (struct ceph_options*) ; 
 int /*<<< orphan*/  ceph_monc_want_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_set_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_mount_options (struct ceph_mount_options*) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 int /*<<< orphan*/  extra_mon_dispatch ; 
 int /*<<< orphan*/  kfree (struct ceph_fs_client*) ; 
 struct ceph_fs_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_kmalloc_pool (int,size_t) ; 

__attribute__((used)) static struct ceph_fs_client *create_fs_client(struct ceph_mount_options *fsopt,
					struct ceph_options *opt)
{
	struct ceph_fs_client *fsc;
	int page_count;
	size_t size;
	int err;

	fsc = kzalloc(sizeof(*fsc), GFP_KERNEL);
	if (!fsc) {
		err = -ENOMEM;
		goto fail;
	}

	fsc->client = ceph_create_client(opt, fsc);
	if (IS_ERR(fsc->client)) {
		err = PTR_ERR(fsc->client);
		goto fail;
	}
	opt = NULL; /* fsc->client now owns this */

	fsc->client->extra_mon_dispatch = extra_mon_dispatch;
	ceph_set_opt(fsc->client, ABORT_ON_FULL);

	if (!fsopt->mds_namespace) {
		ceph_monc_want_map(&fsc->client->monc, CEPH_SUB_MDSMAP,
				   0, true);
	} else {
		ceph_monc_want_map(&fsc->client->monc, CEPH_SUB_FSMAP,
				   0, false);
	}

	fsc->mount_options = fsopt;

	fsc->sb = NULL;
	fsc->mount_state = CEPH_MOUNT_MOUNTING;
	fsc->filp_gen = 1;

	atomic_long_set(&fsc->writeback_count, 0);

	err = -ENOMEM;
	/*
	 * The number of concurrent works can be high but they don't need
	 * to be processed in parallel, limit concurrency.
	 */
	fsc->inode_wq = alloc_workqueue("ceph-inode", WQ_UNBOUND, 0);
	if (!fsc->inode_wq)
		goto fail_client;
	fsc->cap_wq = alloc_workqueue("ceph-cap", 0, 1);
	if (!fsc->cap_wq)
		goto fail_inode_wq;

	/* set up mempools */
	err = -ENOMEM;
	page_count = fsc->mount_options->wsize >> PAGE_SHIFT;
	size = sizeof (struct page *) * (page_count ? page_count : 1);
	fsc->wb_pagevec_pool = mempool_create_kmalloc_pool(10, size);
	if (!fsc->wb_pagevec_pool)
		goto fail_cap_wq;

	return fsc;

fail_cap_wq:
	destroy_workqueue(fsc->cap_wq);
fail_inode_wq:
	destroy_workqueue(fsc->inode_wq);
fail_client:
	ceph_destroy_client(fsc->client);
fail:
	kfree(fsc);
	if (opt)
		ceph_destroy_options(opt);
	destroy_mount_options(fsopt);
	return ERR_PTR(err);
}