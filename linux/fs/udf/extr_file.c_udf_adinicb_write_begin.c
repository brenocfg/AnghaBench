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
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __udf_adinicb_readpage (struct page*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int udf_adinicb_write_begin(struct file *file,
			struct address_space *mapping, loff_t pos,
			unsigned len, unsigned flags, struct page **pagep,
			void **fsdata)
{
	struct page *page;

	if (WARN_ON_ONCE(pos >= PAGE_SIZE))
		return -EIO;
	page = grab_cache_page_write_begin(mapping, 0, flags);
	if (!page)
		return -ENOMEM;
	*pagep = page;

	if (!PageUptodate(page))
		__udf_adinicb_readpage(page);
	return 0;
}