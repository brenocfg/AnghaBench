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
struct file {int f_mode; TYPE_1__* f_mapping; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 unsigned int nfs_page_length (struct page*) ; 
 scalar_t__ pnfs_ld_read_whole_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_want_read_modify_write(struct file *file, struct page *page,
			loff_t pos, unsigned len)
{
	unsigned int pglen = nfs_page_length(page);
	unsigned int offset = pos & (PAGE_SIZE - 1);
	unsigned int end = offset + len;

	if (pnfs_ld_read_whole_page(file->f_mapping->host)) {
		if (!PageUptodate(page))
			return 1;
		return 0;
	}

	if ((file->f_mode & FMODE_READ) &&	/* open for read? */
	    !PageUptodate(page) &&		/* Uptodate? */
	    !PagePrivate(page) &&		/* i/o request already? */
	    pglen &&				/* valid bytes of file? */
	    (end < pglen || offset))		/* replace all valid bytes? */
		return 1;
	return 0;
}