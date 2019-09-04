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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_fill_wb_data {int /*<<< orphan*/  orig_pages; int /*<<< orphan*/ * ff; TYPE_1__* req; struct inode* inode; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_MAX_PAGES_PER_REQ ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  fuse_file_put (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fuse_writepages_fill ; 
 int /*<<< orphan*/  fuse_writepages_send (struct fuse_fill_wb_data*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int write_cache_pages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ,struct fuse_fill_wb_data*) ; 

__attribute__((used)) static int fuse_writepages(struct address_space *mapping,
			   struct writeback_control *wbc)
{
	struct inode *inode = mapping->host;
	struct fuse_fill_wb_data data;
	int err;

	err = -EIO;
	if (is_bad_inode(inode))
		goto out;

	data.inode = inode;
	data.req = NULL;
	data.ff = NULL;

	err = -ENOMEM;
	data.orig_pages = kcalloc(FUSE_MAX_PAGES_PER_REQ,
				  sizeof(struct page *),
				  GFP_NOFS);
	if (!data.orig_pages)
		goto out;

	err = write_cache_pages(mapping, wbc, fuse_writepages_fill, &data);
	if (data.req) {
		/* Ignore errors if we can write at least one page */
		BUG_ON(!data.req->num_pages);
		fuse_writepages_send(&data);
		err = 0;
	}
	if (data.ff)
		fuse_file_put(data.ff, false, false);

	kfree(data.orig_pages);
out:
	return err;
}