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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct file {int dummy; } ;
struct address_space {TYPE_1__* host; } ;
typedef  int loff_t ;
struct TYPE_6__ {unsigned int write_io; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 TYPE_3__* NFS_I (TYPE_1__*) ; 
 int /*<<< orphan*/  PAGECACHE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct file*,int /*<<< orphan*/ ,unsigned int,long long) ; 
 scalar_t__ nfs_ctx_key_to_expire (struct nfs_open_context*,TYPE_1__*) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 unsigned int nfs_page_length (struct page*) ; 
 int nfs_updatepage (struct file*,struct page*,unsigned int,unsigned int) ; 
 int nfs_wb_all (TYPE_1__*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,int) ; 
 int /*<<< orphan*/  zero_user_segments (struct page*,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int nfs_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *page, void *fsdata)
{
	unsigned offset = pos & (PAGE_SIZE - 1);
	struct nfs_open_context *ctx = nfs_file_open_context(file);
	int status;

	dfprintk(PAGECACHE, "NFS: write_end(%pD2(%lu), %u@%lld)\n",
		file, mapping->host->i_ino, len, (long long) pos);

	/*
	 * Zero any uninitialised parts of the page, and then mark the page
	 * as up to date if it turns out that we're extending the file.
	 */
	if (!PageUptodate(page)) {
		unsigned pglen = nfs_page_length(page);
		unsigned end = offset + copied;

		if (pglen == 0) {
			zero_user_segments(page, 0, offset,
					end, PAGE_SIZE);
			SetPageUptodate(page);
		} else if (end >= pglen) {
			zero_user_segment(page, end, PAGE_SIZE);
			if (offset == 0)
				SetPageUptodate(page);
		} else
			zero_user_segment(page, pglen, PAGE_SIZE);
	}

	status = nfs_updatepage(file, page, offset, copied);

	unlock_page(page);
	put_page(page);

	if (status < 0)
		return status;
	NFS_I(mapping->host)->write_io += copied;

	if (nfs_ctx_key_to_expire(ctx, mapping->host)) {
		status = nfs_wb_all(mapping->host);
		if (status < 0)
			return status;
	}

	return copied;
}