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
struct page {struct address_space* mapping; } ;
struct inode {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  error; } ;
struct TYPE_12__ {TYPE_5__ h; TYPE_2__* args; } ;
struct TYPE_7__ {size_t size; } ;
struct TYPE_9__ {int /*<<< orphan*/  attr_ver; TYPE_1__ in; } ;
struct TYPE_10__ {TYPE_3__ read; } ;
struct fuse_req {int num_pages; scalar_t__ ff; TYPE_6__ out; struct page** pages; TYPE_4__ misc; } ;
struct fuse_conn {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_8__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  fuse_file_put (scalar_t__,int,int) ; 
 int /*<<< orphan*/  fuse_invalidate_atime (struct inode*) ; 
 int /*<<< orphan*/  fuse_short_read (struct fuse_req*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void fuse_readpages_end(struct fuse_conn *fc, struct fuse_req *req)
{
	int i;
	size_t count = req->misc.read.in.size;
	size_t num_read = req->out.args[0].size;
	struct address_space *mapping = NULL;

	for (i = 0; mapping == NULL && i < req->num_pages; i++)
		mapping = req->pages[i]->mapping;

	if (mapping) {
		struct inode *inode = mapping->host;

		/*
		 * Short read means EOF. If file size is larger, truncate it
		 */
		if (!req->out.h.error && num_read < count)
			fuse_short_read(req, inode, req->misc.read.attr_ver);

		fuse_invalidate_atime(inode);
	}

	for (i = 0; i < req->num_pages; i++) {
		struct page *page = req->pages[i];
		if (!req->out.h.error)
			SetPageUptodate(page);
		else
			SetPageError(page);
		unlock_page(page);
		put_page(page);
	}
	if (req->ff)
		fuse_file_put(req->ff, false, false);
}