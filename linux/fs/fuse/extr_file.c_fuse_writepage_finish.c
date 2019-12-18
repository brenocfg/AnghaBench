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
struct inode {int dummy; } ;
struct fuse_args_pages {int num_pages; int /*<<< orphan*/ * pages; } ;
struct TYPE_2__ {struct fuse_args_pages ap; } ;
struct fuse_writepage_args {int /*<<< orphan*/  writepages_entry; struct inode* inode; TYPE_1__ ia; } ;
struct fuse_inode {int /*<<< orphan*/  page_waitq; } ;
struct fuse_conn {int dummy; } ;
struct backing_dev_info {int /*<<< orphan*/  wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_WRITEBACK_TEMP ; 
 int /*<<< orphan*/  WB_WRITEBACK ; 
 int /*<<< orphan*/  dec_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_wb_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 struct backing_dev_info* inode_to_bdi (struct inode*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_writeout_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_writepage_finish(struct fuse_conn *fc,
				  struct fuse_writepage_args *wpa)
{
	struct fuse_args_pages *ap = &wpa->ia.ap;
	struct inode *inode = wpa->inode;
	struct fuse_inode *fi = get_fuse_inode(inode);
	struct backing_dev_info *bdi = inode_to_bdi(inode);
	int i;

	list_del(&wpa->writepages_entry);
	for (i = 0; i < ap->num_pages; i++) {
		dec_wb_stat(&bdi->wb, WB_WRITEBACK);
		dec_node_page_state(ap->pages[i], NR_WRITEBACK_TEMP);
		wb_writeout_inc(&bdi->wb);
	}
	wake_up(&fi->page_waitq);
}