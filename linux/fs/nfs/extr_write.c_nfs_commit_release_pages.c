#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {int /*<<< orphan*/  writeback; } ;
struct nfs_page {scalar_t__ wb_page; int /*<<< orphan*/  wb_verf; int /*<<< orphan*/  wb_bytes; } ;
struct nfs_commit_info {int /*<<< orphan*/  mds; } ;
struct TYPE_9__ {int /*<<< orphan*/  verifier; } ;
struct TYPE_11__ {int /*<<< orphan*/  next; } ;
struct TYPE_7__ {int tk_status; } ;
struct nfs_commit_data {int /*<<< orphan*/  dreq; int /*<<< orphan*/  inode; TYPE_3__ verf; TYPE_5__ pages; TYPE_1__ task; } ;
struct TYPE_12__ {TYPE_2__* d_sb; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; TYPE_6__* dentry; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 scalar_t__ NFS_CONGESTION_OFF_THRESH ; 
 int /*<<< orphan*/  NFS_CONTEXT_RESEND_WRITES ; 
 scalar_t__ NFS_FILEID (int /*<<< orphan*/ ) ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  d_inode (TYPE_6__*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  dprintk_cont (char*,...) ; 
 int /*<<< orphan*/  inode_to_bdi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (TYPE_5__*) ; 
 int /*<<< orphan*/  nfs_clear_page_commit (scalar_t__) ; 
 int /*<<< orphan*/  nfs_commit_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_cinfo (struct nfs_commit_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inode_remove_request (struct nfs_page*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mapping_set_error (scalar_t__,int) ; 
 int /*<<< orphan*/  nfs_mark_request_dirty (struct nfs_page*) ; 
 TYPE_4__* nfs_req_openctx (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_write_verifier_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_commit_release_pages(struct nfs_commit_data *data)
{
	struct nfs_page	*req;
	int status = data->task.tk_status;
	struct nfs_commit_info cinfo;
	struct nfs_server *nfss;

	while (!list_empty(&data->pages)) {
		req = nfs_list_entry(data->pages.next);
		nfs_list_remove_request(req);
		if (req->wb_page)
			nfs_clear_page_commit(req->wb_page);

		dprintk("NFS:       commit (%s/%llu %d@%lld)",
			nfs_req_openctx(req)->dentry->d_sb->s_id,
			(unsigned long long)NFS_FILEID(d_inode(nfs_req_openctx(req)->dentry)),
			req->wb_bytes,
			(long long)req_offset(req));
		if (status < 0) {
			if (req->wb_page) {
				nfs_mapping_set_error(req->wb_page, status);
				nfs_inode_remove_request(req);
			}
			dprintk_cont(", error = %d\n", status);
			goto next;
		}

		/* Okay, COMMIT succeeded, apparently. Check the verifier
		 * returned by the server against all stored verfs. */
		if (!nfs_write_verifier_cmp(&req->wb_verf, &data->verf.verifier)) {
			/* We have a match */
			if (req->wb_page)
				nfs_inode_remove_request(req);
			dprintk_cont(" OK\n");
			goto next;
		}
		/* We have a mismatch. Write the page again */
		dprintk_cont(" mismatch\n");
		nfs_mark_request_dirty(req);
		set_bit(NFS_CONTEXT_RESEND_WRITES, &nfs_req_openctx(req)->flags);
	next:
		nfs_unlock_and_release_request(req);
		/* Latency breaker */
		cond_resched();
	}
	nfss = NFS_SERVER(data->inode);
	if (atomic_long_read(&nfss->writeback) < NFS_CONGESTION_OFF_THRESH)
		clear_bdi_congested(inode_to_bdi(data->inode), BLK_RW_ASYNC);

	nfs_init_cinfo(&cinfo, data->inode, data->dreq);
	nfs_commit_end(cinfo.mds);
}