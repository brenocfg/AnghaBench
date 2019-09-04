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
struct nfs_server {int /*<<< orphan*/  writeback; } ;
struct nfs_page {int /*<<< orphan*/  wb_page; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 scalar_t__ NFS_CONGESTION_OFF_THRESH ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  PG_WB_END ; 
 scalar_t__ atomic_long_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_to_bdi (struct inode*) ; 
 int nfs_page_group_sync_on_bit (struct nfs_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_unlock_request (struct nfs_page*) ; 
 TYPE_1__* page_file_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_end_page_writeback(struct nfs_page *req)
{
	struct inode *inode = page_file_mapping(req->wb_page)->host;
	struct nfs_server *nfss = NFS_SERVER(inode);
	bool is_done;

	is_done = nfs_page_group_sync_on_bit(req, PG_WB_END);
	nfs_unlock_request(req);
	if (!is_done)
		return;

	end_page_writeback(req->wb_page);
	if (atomic_long_dec_return(&nfss->writeback) < NFS_CONGESTION_OFF_THRESH)
		clear_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);
}