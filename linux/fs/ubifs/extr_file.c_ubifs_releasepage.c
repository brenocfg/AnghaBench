#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {TYPE_2__* i_sb; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {struct ubifs_info* s_fs_info; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ubifs_releasepage(struct page *page, gfp_t unused_gfp_flags)
{
	struct inode *inode = page->mapping->host;
	struct ubifs_info *c = inode->i_sb->s_fs_info;

	/*
	 * An attempt to release a dirty page without budgeting for it - should
	 * not happen.
	 */
	if (PageWriteback(page))
		return 0;
	ubifs_assert(c, PagePrivate(page));
	ubifs_assert(c, 0);
	ClearPagePrivate(page);
	ClearPageChecked(page);
	return 1;
}