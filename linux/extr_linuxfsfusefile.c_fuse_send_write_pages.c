#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; } ;
struct kiocb {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct TYPE_6__ {TYPE_2__ h; } ;
struct fuse_req {unsigned int num_pages; TYPE_3__ out; struct page** pages; TYPE_1__* page_descs; } ;
struct fuse_io_priv {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {unsigned int offset; } ;

/* Variables and functions */
 struct fuse_io_priv FUSE_IO_PRIV_SYNC (struct kiocb*) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 size_t fuse_send_write (struct fuse_req*,struct fuse_io_priv*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_wait_on_page_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static size_t fuse_send_write_pages(struct fuse_req *req, struct kiocb *iocb,
				    struct inode *inode, loff_t pos,
				    size_t count)
{
	size_t res;
	unsigned offset;
	unsigned i;
	struct fuse_io_priv io = FUSE_IO_PRIV_SYNC(iocb);

	for (i = 0; i < req->num_pages; i++)
		fuse_wait_on_page_writeback(inode, req->pages[i]->index);

	res = fuse_send_write(req, &io, pos, count, NULL);

	offset = req->page_descs[0].offset;
	count = res;
	for (i = 0; i < req->num_pages; i++) {
		struct page *page = req->pages[i];

		if (!req->out.h.error && !offset && count >= PAGE_SIZE)
			SetPageUptodate(page);

		if (count > PAGE_SIZE - offset)
			count -= PAGE_SIZE - offset;
		else
			count = 0;
		offset = 0;

		unlock_page(page);
		put_page(page);
	}

	return res;
}