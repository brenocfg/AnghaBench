#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  verifier; } ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
struct nfs_pgio_header {unsigned long good_bytes; int /*<<< orphan*/  (* release ) (struct nfs_pgio_header*) ;int /*<<< orphan*/  io_completion; int /*<<< orphan*/  pgio_mirror_idx; int /*<<< orphan*/  lseg; TYPE_1__ verf; int /*<<< orphan*/  error; int /*<<< orphan*/  flags; TYPE_2__ pages; int /*<<< orphan*/  inode; } ;
struct nfs_page {int /*<<< orphan*/  wb_verf; scalar_t__ wb_nio; int /*<<< orphan*/  wb_page; scalar_t__ wb_bytes; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_ERROR ; 
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs_end_page_writeback (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_inode (struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inode_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_io_completion_put (int /*<<< orphan*/ ) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mapping_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_mark_request_commit (struct nfs_page*,int /*<<< orphan*/ ,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_set_pageerror (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_write_need_commit (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  page_file_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_write_completion(struct nfs_pgio_header *hdr)
{
	struct nfs_commit_info cinfo;
	unsigned long bytes = 0;

	if (test_bit(NFS_IOHDR_REDO, &hdr->flags))
		goto out;
	nfs_init_cinfo_from_inode(&cinfo, hdr->inode);
	while (!list_empty(&hdr->pages)) {
		struct nfs_page *req = nfs_list_entry(hdr->pages.next);

		bytes += req->wb_bytes;
		nfs_list_remove_request(req);
		if (test_bit(NFS_IOHDR_ERROR, &hdr->flags) &&
		    (hdr->good_bytes < bytes)) {
			nfs_set_pageerror(page_file_mapping(req->wb_page));
			nfs_mapping_set_error(req->wb_page, hdr->error);
			goto remove_req;
		}
		if (nfs_write_need_commit(hdr)) {
			/* Reset wb_nio, since the write was successful. */
			req->wb_nio = 0;
			memcpy(&req->wb_verf, &hdr->verf.verifier, sizeof(req->wb_verf));
			nfs_mark_request_commit(req, hdr->lseg, &cinfo,
				hdr->pgio_mirror_idx);
			goto next;
		}
remove_req:
		nfs_inode_remove_request(req);
next:
		nfs_end_page_writeback(req);
		nfs_release_request(req);
	}
out:
	nfs_io_completion_put(hdr->io_completion);
	hdr->release(hdr);
}