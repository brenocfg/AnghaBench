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
typedef  int /*<<< orphan*/  u64 ;
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct fuse_page_desc {scalar_t__ length; } ;
struct TYPE_5__ {int page_zeroing; int out_pages; } ;
struct TYPE_6__ {int num_pages; TYPE_2__ args; struct fuse_page_desc* descs; struct page** pages; } ;
struct fuse_io_args {TYPE_3__ ap; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_READ ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  fuse_get_attr_version (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_read_args_fill (struct fuse_io_args*,struct file*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_short_read (struct inode*,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 scalar_t__ fuse_simple_request (struct fuse_conn*,TYPE_2__*) ; 
 int /*<<< orphan*/  fuse_wait_on_page_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  page_offset (struct page*) ; 

__attribute__((used)) static int fuse_do_readpage(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	loff_t pos = page_offset(page);
	struct fuse_page_desc desc = { .length = PAGE_SIZE };
	struct fuse_io_args ia = {
		.ap.args.page_zeroing = true,
		.ap.args.out_pages = true,
		.ap.num_pages = 1,
		.ap.pages = &page,
		.ap.descs = &desc,
	};
	ssize_t res;
	u64 attr_ver;

	/*
	 * Page writeback can extend beyond the lifetime of the
	 * page-cache page, so make sure we read a properly synced
	 * page.
	 */
	fuse_wait_on_page_writeback(inode, page->index);

	attr_ver = fuse_get_attr_version(fc);

	fuse_read_args_fill(&ia, file, pos, desc.length, FUSE_READ);
	res = fuse_simple_request(fc, &ia.ap.args);
	if (res < 0)
		return res;
	/*
	 * Short read means EOF.  If file size is larger, truncate it
	 */
	if (res < desc.length)
		fuse_short_read(inode, attr_ver, res, &ia.ap);

	SetPageUptodate(page);

	return 0;
}