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
struct page {int dummy; } ;
struct inode {int i_size; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 TYPE_1__* FILE_HOSTFS_I (struct file*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int write_file (int /*<<< orphan*/ ,int*,void*,unsigned int) ; 

__attribute__((used)) static int hostfs_write_end(struct file *file, struct address_space *mapping,
			    loff_t pos, unsigned len, unsigned copied,
			    struct page *page, void *fsdata)
{
	struct inode *inode = mapping->host;
	void *buffer;
	unsigned from = pos & (PAGE_SIZE - 1);
	int err;

	buffer = kmap(page);
	err = write_file(FILE_HOSTFS_I(file)->fd, &pos, buffer + from, copied);
	kunmap(page);

	if (!PageUptodate(page) && err == PAGE_SIZE)
		SetPageUptodate(page);

	/*
	 * If err > 0, write_file has added err to pos, so we are comparing
	 * i_size against the last byte written.
	 */
	if (err > 0 && (pos > inode->i_size))
		inode->i_size = pos;
	unlock_page(page);
	put_page(page);

	return err;
}