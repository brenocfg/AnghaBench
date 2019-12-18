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
struct page {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  writeback; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 scalar_t__ NFS_CONGESTION_ON_THRESH ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_long_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_to_bdi (struct inode*) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 
 int /*<<< orphan*/  set_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_set_page_writeback (struct page*) ; 

__attribute__((used)) static void nfs_set_page_writeback(struct page *page)
{
	struct inode *inode = page_file_mapping(page)->host;
	struct nfs_server *nfss = NFS_SERVER(inode);
	int ret = test_set_page_writeback(page);

	WARN_ON_ONCE(ret != 0);

	if (atomic_long_inc_return(&nfss->writeback) >
			NFS_CONGESTION_ON_THRESH)
		set_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);
}