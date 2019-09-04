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
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  reiserfs_wait_on_write_block (int /*<<< orphan*/ ) ; 
 int reiserfs_write_full_page (struct page*,struct writeback_control*) ; 

__attribute__((used)) static int reiserfs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	reiserfs_wait_on_write_block(inode->i_sb);
	return reiserfs_write_full_page(page, wbc);
}