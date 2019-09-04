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
struct page {TYPE_1__* mapping; } ;
struct inode {unsigned int i_size; } ;
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int udf_adinicb_write_end(struct file *file, struct address_space *mapping,
				 loff_t pos, unsigned len, unsigned copied,
				 struct page *page, void *fsdata)
{
	struct inode *inode = page->mapping->host;
	loff_t last_pos = pos + copied;
	if (last_pos > inode->i_size)
		i_size_write(inode, last_pos);
	set_page_dirty(page);
	unlock_page(page);
	put_page(page);
	return copied;
}