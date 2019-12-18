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
struct ufs_dir_entry {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 scalar_t__ page_address (struct page*) ; 
 struct page* ufs_get_page (struct inode*,int /*<<< orphan*/ ) ; 
 struct ufs_dir_entry* ufs_next_entry (int /*<<< orphan*/ ,struct ufs_dir_entry*) ; 

struct ufs_dir_entry *ufs_dotdot(struct inode *dir, struct page **p)
{
	struct page *page = ufs_get_page(dir, 0);
	struct ufs_dir_entry *de = NULL;

	if (!IS_ERR(page)) {
		de = ufs_next_entry(dir->i_sb,
				    (struct ufs_dir_entry *)page_address(page));
		*p = page;
	}
	return de;
}