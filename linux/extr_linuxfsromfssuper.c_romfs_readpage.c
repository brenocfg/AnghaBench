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
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
typedef  unsigned long loff_t ;
struct TYPE_4__ {unsigned long i_dataoffset; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 unsigned long PAGE_SIZE ; 
 TYPE_2__* ROMFS_I (struct inode*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 unsigned long i_size_read (struct inode*) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long page_offset (struct page*) ; 
 int romfs_dev_read (int /*<<< orphan*/ ,unsigned long,void*,unsigned long) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int romfs_readpage(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	loff_t offset, size;
	unsigned long fillsize, pos;
	void *buf;
	int ret;

	buf = kmap(page);
	if (!buf)
		return -ENOMEM;

	/* 32 bit warning -- but not for us :) */
	offset = page_offset(page);
	size = i_size_read(inode);
	fillsize = 0;
	ret = 0;
	if (offset < size) {
		size -= offset;
		fillsize = size > PAGE_SIZE ? PAGE_SIZE : size;

		pos = ROMFS_I(inode)->i_dataoffset + offset;

		ret = romfs_dev_read(inode->i_sb, pos, buf, fillsize);
		if (ret < 0) {
			SetPageError(page);
			fillsize = 0;
			ret = -EIO;
		}
	}

	if (fillsize < PAGE_SIZE)
		memset(buf + fillsize, 0, PAGE_SIZE - fillsize);
	if (ret == 0)
		SetPageUptodate(page);

	flush_dcache_page(page);
	kunmap(page);
	unlock_page(page);
	return ret;
}