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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 TYPE_1__* FILE_HOSTFS_I (struct file*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  page_offset (struct page*) ; 
 int read_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int hostfs_readpage(struct file *file, struct page *page)
{
	char *buffer;
	loff_t start = page_offset(page);
	int bytes_read, ret = 0;

	buffer = kmap(page);
	bytes_read = read_file(FILE_HOSTFS_I(file)->fd, &start, buffer,
			PAGE_SIZE);
	if (bytes_read < 0) {
		ClearPageUptodate(page);
		SetPageError(page);
		ret = bytes_read;
		goto out;
	}

	memset(buffer + bytes_read, 0, PAGE_SIZE - bytes_read);

	ClearPageError(page);
	SetPageUptodate(page);

 out:
	flush_dcache_page(page);
	kunmap(page);
	unlock_page(page);
	return ret;
}