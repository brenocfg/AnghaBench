#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct ceph_options {int dummy; } ;
struct ceph_mount_options {int wsize; int /*<<< orphan*/  max_readdir; int /*<<< orphan*/  mds_namespace; } ;
struct ceph_fs_client {TYPE_2__* client; void* wb_wq; void* pg_inv_wq; void* trunc_wq; int /*<<< orphan*/  min_caps; int /*<<< orphan*/  wb_pagevec_pool; struct ceph_mount_options* mount_options; int /*<<< orphan*/  writeback_count; int /*<<< orphan*/  mount_state; int /*<<< orphan*/ * sb; } ;
struct TYPE_6__ {int abort_on_full; } ;
struct TYPE_7__ {int /*<<< orphan*/  monc; TYPE_1__ osdc; int /*<<< orphan*/  extra_mon_dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MOUNT_MOUNTING ; 
 int /*<<< orphan*/  CEPH_SUB_FSMAP ; 
 int /*<<< orphan*/  CEPH_SUB_MDSMAP ; 
 int ENOMEM ; 
 struct ceph_fs_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (TYPE_2__*) ; 
 void* alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ceph_create_client (struct ceph_options*,struct ceph_fs_client*) ; 
 int /*<<< orphan*/  ceph_destroy_client (TYPE_2__*) ; 
 int /*<<< orphan*/  ceph_destroy_options (struct ceph_options*) ; 
 int /*<<< orphan*/  ceph_monc_want_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
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
	fsc->client->osdc.abort_on_full = true;

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

	atomic_long_set(&fsc->writeback_count, 0);

	err = -ENOMEM;
	/*
	 * The number of concurrent works can be high but they don't need
	 * to be processed in parallel, limit concurrency.
	 */
	fsc->wb_wq = alloc_workqueue("ceph-writeback", 0, 1);
	if (!fsc->wb_wq)
		goto fail_client;
	fsc->pg_inv_wq = alloc_workqueue("ceph-pg-invalid", 0, 1);
	if (!fsc->pg_inv_wq)
		goto fail_wb_wq;
	fsc->trunc_wq = alloc_workqueue("ceph-trunc", 0, 1);
	if (!fsc->trunc_wq)
		goto fail_pg_inv_wq;

	/* set up mempools */
	err = -ENOMEM;
	page_count = fsc->mount_options->wsize >> PAGE_SHIFT;
	size = sizeof (struct page *) * (page_count ? page_count : 1);
	fsc->wb_pagevec_pool = mempool_create_kmalloc_pool(10, size);
	if (!fsc->wb_pagevec_pool)
		goto fail_trunc_wq;

	/* caps */
	fsc->min_caps = fsopt->max_readdir;

	return fsc;

fail_trunc_wq:
	destroy_workqueue(fsc->trunc_wq);
fail_pg_inv_wq:
	destroy_workqueue(fsc->pg_inv_wq);
fail_wb_wq:
	destroy_workqueue(fsc->wb_wq);
fail_client:
	ceph_destroy_client(fsc->client);
fail:
	kfree(fsc);
	if (opt)
		ceph_destroy_options(opt);
	destroy_mount_options(fsopt);
	return ERR_PTR(err);
}