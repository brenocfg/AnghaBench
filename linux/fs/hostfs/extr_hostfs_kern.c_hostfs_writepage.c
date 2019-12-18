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
struct page {int index; struct address_space* mapping; } ;
struct inode {int i_size; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 TYPE_1__* HOSTFS_I (struct inode*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ PageError (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int write_file (int /*<<< orphan*/ ,int*,char*,int) ; 

__attribute__((used)) static int hostfs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct address_space *mapping = page->mapping;
	struct inode *inode = mapping->host;
	char *buffer;
	loff_t base = page_offset(page);
	int count = PAGE_SIZE;
	int end_index = inode->i_size >> PAGE_SHIFT;
	int err;

	if (page->index >= end_index)
		count = inode->i_size & (PAGE_SIZE-1);

	buffer = kmap(page);

	err = write_file(HOSTFS_I(inode)->fd, &base, buffer, count);
	if (err != count) {
		ClearPageUptodate(page);
		goto out;
	}

	if (base > inode->i_size)
		inode->i_size = base;

	if (PageError(page))
		ClearPageError(page);
	err = 0;

 out:
	kunmap(page);

	unlock_page(page);
	return err;
}