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
struct page {scalar_t__ index; } ;
struct file {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXOFS_DBGMSG (char*) ; 
 scalar_t__ PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int _readpage (struct page*,int) ; 
 int /*<<< orphan*/  clear_highpage (struct page*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,scalar_t__,unsigned int) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int exofs_write_begin(struct file *file, struct address_space *mapping,
		loff_t pos, unsigned len, unsigned flags,
		struct page **pagep, void **fsdata)
{
	int ret = 0;
	struct page *page;

	page = *pagep;
	if (page == NULL) {
		page = grab_cache_page_write_begin(mapping, pos >> PAGE_SHIFT,
						   flags);
		if (!page) {
			EXOFS_DBGMSG("grab_cache_page_write_begin failed\n");
			return -ENOMEM;
		}
		*pagep = page;
	}

	 /* read modify write */
	if (!PageUptodate(page) && (len != PAGE_SIZE)) {
		loff_t i_size = i_size_read(mapping->host);
		pgoff_t end_index = i_size >> PAGE_SHIFT;

		if (page->index > end_index) {
			clear_highpage(page);
			SetPageUptodate(page);
		} else {
			ret = _readpage(page, true);
			if (ret) {
				unlock_page(page);
				EXOFS_DBGMSG("__readpage failed\n");
			}
		}
	}
	return ret;
}