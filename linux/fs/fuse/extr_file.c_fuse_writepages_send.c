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
struct inode {int dummy; } ;
struct TYPE_3__ {int num_pages; } ;
struct TYPE_4__ {int /*<<< orphan*/  ff; TYPE_1__ ap; } ;
struct fuse_writepage_args {int /*<<< orphan*/  queue_entry; TYPE_2__ ia; } ;
struct fuse_inode {int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_writes; } ;
struct fuse_fill_wb_data {int /*<<< orphan*/ * orig_pages; int /*<<< orphan*/  ff; struct inode* inode; struct fuse_writepage_args* wpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_page_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_file_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_flush_writepages (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_writepages_send(struct fuse_fill_wb_data *data)
{
	struct fuse_writepage_args *wpa = data->wpa;
	struct inode *inode = data->inode;
	struct fuse_inode *fi = get_fuse_inode(inode);
	int num_pages = wpa->ia.ap.num_pages;
	int i;

	wpa->ia.ff = fuse_file_get(data->ff);
	spin_lock(&fi->lock);
	list_add_tail(&wpa->queue_entry, &fi->queued_writes);
	fuse_flush_writepages(inode);
	spin_unlock(&fi->lock);

	for (i = 0; i < num_pages; i++)
		end_page_writeback(data->orig_pages[i]);
}