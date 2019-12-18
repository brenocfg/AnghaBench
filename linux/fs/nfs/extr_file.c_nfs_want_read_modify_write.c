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
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FMODE_READ ; 
 scalar_t__ PagePrivate (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 scalar_t__ nfs_full_page_write (struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ pnfs_ld_read_whole_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfs_want_read_modify_write(struct file *file, struct page *page,
			loff_t pos, unsigned int len)
{
	/*
	 * Up-to-date pages, those with ongoing or full-page write
	 * don't need read/modify/write
	 */
	if (PageUptodate(page) || PagePrivate(page) ||
	    nfs_full_page_write(page, pos, len))
		return false;

	if (pnfs_ld_read_whole_page(file->f_mapping->host))
		return true;
	/* Open for reading too? */
	if (file->f_mode & FMODE_READ)
		return true;
	return false;
}