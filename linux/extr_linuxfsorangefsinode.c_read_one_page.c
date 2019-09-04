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
struct page {int index; TYPE_1__* mapping; } ;
struct iov_iter {int dummy; } ;
struct inode {int const i_size; } ;
struct bio_vec {int bv_len; struct page* bv_page; } ;
typedef  int ssize_t ;
typedef  int const loff_t ;
typedef  int __u32 ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  GOSSIP_INODE_DEBUG ; 
 int ITER_BVEC ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ PageError (struct page*) ; 
 int READ ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,struct page*) ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int,struct bio_vec*,int,int) ; 
 int /*<<< orphan*/  iov_iter_zero (unsigned int,struct iov_iter*) ; 
 int orangefs_inode_read (struct inode*,struct iov_iter*,int const*,int const) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int read_one_page(struct page *page)
{
	int ret;
	int max_block;
	ssize_t bytes_read = 0;
	struct inode *inode = page->mapping->host;
	const __u32 blocksize = PAGE_SIZE;
	const __u32 blockbits = PAGE_SHIFT;
	struct iov_iter to;
	struct bio_vec bv = {.bv_page = page, .bv_len = PAGE_SIZE};

	iov_iter_bvec(&to, ITER_BVEC | READ, &bv, 1, PAGE_SIZE);

	gossip_debug(GOSSIP_INODE_DEBUG,
		    "orangefs_readpage called with page %p\n",
		     page);

	max_block = ((inode->i_size / blocksize) + 1);

	if (page->index < max_block) {
		loff_t blockptr_offset = (((loff_t) page->index) << blockbits);

		bytes_read = orangefs_inode_read(inode,
						 &to,
						 &blockptr_offset,
						 inode->i_size);
	}
	/* this will only zero remaining unread portions of the page data */
	iov_iter_zero(~0U, &to);
	/* takes care of potential aliasing */
	flush_dcache_page(page);
	if (bytes_read < 0) {
		ret = bytes_read;
		SetPageError(page);
	} else {
		SetPageUptodate(page);
		if (PageError(page))
			ClearPageError(page);
		ret = 0;
	}
	/* unlock the page after the ->readpage() routine completes */
	unlock_page(page);
	return ret;
}