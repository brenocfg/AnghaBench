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
struct address_space {int dummy; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 struct page* grab_cache_page (struct address_space*,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,int) ; 

__attribute__((used)) static int cifs_truncate_page(struct address_space *mapping, loff_t from)
{
	pgoff_t index = from >> PAGE_SHIFT;
	unsigned offset = from & (PAGE_SIZE - 1);
	struct page *page;
	int rc = 0;

	page = grab_cache_page(mapping, index);
	if (!page)
		return -ENOMEM;

	zero_user_segment(page, offset, PAGE_SIZE);
	unlock_page(page);
	put_page(page);
	return rc;
}