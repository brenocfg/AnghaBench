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
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct page *ecryptfs_get_locked_page(struct inode *inode, loff_t index)
{
	struct page *page = read_mapping_page(inode->i_mapping, index, NULL);
	if (!IS_ERR(page))
		lock_page(page);
	return page;
}