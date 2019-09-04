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
struct page_collect {unsigned int expected_pages; int pg_first; int read_4_write; int /*<<< orphan*/ * that_locked_page; scalar_t__ length; scalar_t__ nr_pages; scalar_t__ alloc_pages; int /*<<< orphan*/ * pages; int /*<<< orphan*/ * ios; struct inode* inode; struct exofs_sb_info* sbi; } ;
struct inode {TYPE_1__* i_sb; } ;
struct exofs_sb_info {int dummy; } ;
struct TYPE_2__ {struct exofs_sb_info* s_fs_info; } ;

/* Variables and functions */

__attribute__((used)) static void _pcol_init(struct page_collect *pcol, unsigned expected_pages,
		       struct inode *inode)
{
	struct exofs_sb_info *sbi = inode->i_sb->s_fs_info;

	pcol->sbi = sbi;
	pcol->inode = inode;
	pcol->expected_pages = expected_pages;

	pcol->ios = NULL;
	pcol->pages = NULL;
	pcol->alloc_pages = 0;
	pcol->nr_pages = 0;
	pcol->length = 0;
	pcol->pg_first = -1;
	pcol->read_4_write = false;
	pcol->that_locked_page = NULL;
}