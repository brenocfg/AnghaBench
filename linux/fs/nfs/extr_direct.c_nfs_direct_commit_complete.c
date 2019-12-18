#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfs_page {scalar_t__ wb_nio; } ;
struct nfs_direct_req {scalar_t__ flags; } ;
struct nfs_commit_info {TYPE_2__* mds; } ;
struct TYPE_6__ {int /*<<< orphan*/  next; } ;
struct TYPE_4__ {int tk_status; } ;
struct nfs_commit_data {TYPE_3__ pages; TYPE_1__ task; struct nfs_direct_req* dreq; } ;
struct TYPE_5__ {int /*<<< orphan*/  rpcs_out; } ;

/* Variables and functions */
 scalar_t__ NFS_ODIRECT_RESCHED_WRITES ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_3__*) ; 
 scalar_t__ nfs_direct_cmp_commit_data_verf (struct nfs_direct_req*,struct nfs_commit_data*) ; 
 int /*<<< orphan*/  nfs_direct_write_complete (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_dreq (struct nfs_commit_info*,struct nfs_direct_req*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mark_request_commit (struct nfs_page*,int /*<<< orphan*/ *,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 

__attribute__((used)) static void nfs_direct_commit_complete(struct nfs_commit_data *data)
{
	struct nfs_direct_req *dreq = data->dreq;
	struct nfs_commit_info cinfo;
	struct nfs_page *req;
	int status = data->task.tk_status;

	nfs_init_cinfo_from_dreq(&cinfo, dreq);
	if (status < 0 || nfs_direct_cmp_commit_data_verf(dreq, data))
		dreq->flags = NFS_ODIRECT_RESCHED_WRITES;

	while (!list_empty(&data->pages)) {
		req = nfs_list_entry(data->pages.next);
		nfs_list_remove_request(req);
		if (dreq->flags == NFS_ODIRECT_RESCHED_WRITES) {
			/*
			 * Despite the reboot, the write was successful,
			 * so reset wb_nio.
			 */
			req->wb_nio = 0;
			/* Note the rewrite will go through mds */
			nfs_mark_request_commit(req, NULL, &cinfo, 0);
		} else
			nfs_release_request(req);
		nfs_unlock_and_release_request(req);
	}

	if (atomic_dec_and_test(&cinfo.mds->rpcs_out))
		nfs_direct_write_complete(dreq);
}