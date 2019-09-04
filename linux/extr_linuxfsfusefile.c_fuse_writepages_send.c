#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_req {int num_pages; int /*<<< orphan*/  list; int /*<<< orphan*/  ff; } ;
struct fuse_inode {int /*<<< orphan*/  queued_writes; } ;
struct fuse_fill_wb_data {int /*<<< orphan*/ * orig_pages; int /*<<< orphan*/  ff; struct inode* inode; struct fuse_req* req; } ;
struct fuse_conn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_page_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_file_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_flush_writepages (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_writepages_send(struct fuse_fill_wb_data *data)
{
	struct fuse_req *req = data->req;
	struct inode *inode = data->inode;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);
	int num_pages = req->num_pages;
	int i;

	req->ff = fuse_file_get(data->ff);
	spin_lock(&fc->lock);
	list_add_tail(&req->list, &fi->queued_writes);
	fuse_flush_writepages(inode);
	spin_unlock(&fc->lock);

	for (i = 0; i < num_pages; i++)
		end_page_writeback(data->orig_pages[i]);
}