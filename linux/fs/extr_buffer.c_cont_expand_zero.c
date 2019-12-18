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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  unsigned int pgoff_t ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINTR ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  balance_dirty_pages_ratelimited (struct address_space*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 unsigned int i_blocksize (struct inode*) ; 
 int pagecache_write_begin (struct file*,struct address_space*,unsigned int,unsigned int,int /*<<< orphan*/ ,struct page**,void**) ; 
 int pagecache_write_end (struct file*,struct address_space*,unsigned int,unsigned int,unsigned int,struct page*,void*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static int cont_expand_zero(struct file *file, struct address_space *mapping,
			    loff_t pos, loff_t *bytes)
{
	struct inode *inode = mapping->host;
	unsigned int blocksize = i_blocksize(inode);
	struct page *page;
	void *fsdata;
	pgoff_t index, curidx;
	loff_t curpos;
	unsigned zerofrom, offset, len;
	int err = 0;

	index = pos >> PAGE_SHIFT;
	offset = pos & ~PAGE_MASK;

	while (index > (curidx = (curpos = *bytes)>>PAGE_SHIFT)) {
		zerofrom = curpos & ~PAGE_MASK;
		if (zerofrom & (blocksize-1)) {
			*bytes |= (blocksize-1);
			(*bytes)++;
		}
		len = PAGE_SIZE - zerofrom;

		err = pagecache_write_begin(file, mapping, curpos, len, 0,
					    &page, &fsdata);
		if (err)
			goto out;
		zero_user(page, zerofrom, len);
		err = pagecache_write_end(file, mapping, curpos, len, len,
						page, fsdata);
		if (err < 0)
			goto out;
		BUG_ON(err != len);
		err = 0;

		balance_dirty_pages_ratelimited(mapping);

		if (fatal_signal_pending(current)) {
			err = -EINTR;
			goto out;
		}
	}

	/* page covers the boundary, find the boundary offset */
	if (index == curidx) {
		zerofrom = curpos & ~PAGE_MASK;
		/* if we will expand the thing last block will be filled */
		if (offset <= zerofrom) {
			goto out;
		}
		if (zerofrom & (blocksize-1)) {
			*bytes |= (blocksize-1);
			(*bytes)++;
		}
		len = offset - zerofrom;

		err = pagecache_write_begin(file, mapping, curpos, len, 0,
					    &page, &fsdata);
		if (err)
			goto out;
		zero_user(page, zerofrom, len);
		err = pagecache_write_end(file, mapping, curpos, len, len,
						page, fsdata);
		if (err < 0)
			goto out;
		BUG_ON(err != len);
		err = 0;
	}
out:
	return err;
}