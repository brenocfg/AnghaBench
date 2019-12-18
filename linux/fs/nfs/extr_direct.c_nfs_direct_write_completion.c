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
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct nfs_pgio_header {scalar_t__ good_bytes; int /*<<< orphan*/  (* release ) (struct nfs_pgio_header*) ;int /*<<< orphan*/  ds_commit_idx; int /*<<< orphan*/  lseg; TYPE_1__ pages; int /*<<< orphan*/  flags; struct nfs_direct_req* dreq; } ;
struct nfs_page {int /*<<< orphan*/  wb_kref; } ;
struct nfs_direct_req {scalar_t__ flags; int /*<<< orphan*/  lock; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 scalar_t__ NFS_ODIRECT_DO_COMMIT ; 
 scalar_t__ NFS_ODIRECT_RESCHED_WRITES ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_direct_count_bytes (struct nfs_direct_req*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  nfs_direct_set_hdr_verf (struct nfs_direct_req*,struct nfs_pgio_header*) ; 
 scalar_t__ nfs_direct_set_or_cmp_hdr_verf (struct nfs_direct_req*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  nfs_direct_write_complete (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_dreq (struct nfs_commit_info*,struct nfs_direct_req*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mark_request_commit (struct nfs_page*,int /*<<< orphan*/ ,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 
 scalar_t__ nfs_write_need_commit (struct nfs_pgio_header*) ; 
 scalar_t__ put_dreq (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_direct_write_completion(struct nfs_pgio_header *hdr)
{
	struct nfs_direct_req *dreq = hdr->dreq;
	struct nfs_commit_info cinfo;
	bool request_commit = false;
	struct nfs_page *req = nfs_list_entry(hdr->pages.next);

	nfs_init_cinfo_from_dreq(&cinfo, dreq);

	spin_lock(&dreq->lock);
	if (test_bit(NFS_IOHDR_REDO, &hdr->flags)) {
		spin_unlock(&dreq->lock);
		goto out_put;
	}

	nfs_direct_count_bytes(dreq, hdr);
	if (hdr->good_bytes != 0) {
		if (nfs_write_need_commit(hdr)) {
			if (dreq->flags == NFS_ODIRECT_RESCHED_WRITES)
				request_commit = true;
			else if (dreq->flags == 0) {
				nfs_direct_set_hdr_verf(dreq, hdr);
				request_commit = true;
				dreq->flags = NFS_ODIRECT_DO_COMMIT;
			} else if (dreq->flags == NFS_ODIRECT_DO_COMMIT) {
				request_commit = true;
				if (nfs_direct_set_or_cmp_hdr_verf(dreq, hdr))
					dreq->flags =
						NFS_ODIRECT_RESCHED_WRITES;
			}
		}
	}
	spin_unlock(&dreq->lock);

	while (!list_empty(&hdr->pages)) {

		req = nfs_list_entry(hdr->pages.next);
		nfs_list_remove_request(req);
		if (request_commit) {
			kref_get(&req->wb_kref);
			nfs_mark_request_commit(req, hdr->lseg, &cinfo,
				hdr->ds_commit_idx);
		}
		nfs_unlock_and_release_request(req);
	}

out_put:
	if (put_dreq(dreq))
		nfs_direct_write_complete(dreq);
	hdr->release(hdr);
}