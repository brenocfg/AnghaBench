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
struct ubifs_inode {int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  dirty; } ;
struct ubifs_info {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageChecked (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_existing_page_budget (struct ubifs_info*) ; 
 int /*<<< orphan*/  release_new_page_budget (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_release_dirty_inode_budget (struct ubifs_info*,struct ubifs_inode*) ; 

__attribute__((used)) static void cancel_budget(struct ubifs_info *c, struct page *page,
			  struct ubifs_inode *ui, int appending)
{
	if (appending) {
		if (!ui->dirty)
			ubifs_release_dirty_inode_budget(c, ui);
		mutex_unlock(&ui->ui_mutex);
	}
	if (!PagePrivate(page)) {
		if (PageChecked(page))
			release_new_page_budget(c);
		else
			release_existing_page_budget(c);
	}
}