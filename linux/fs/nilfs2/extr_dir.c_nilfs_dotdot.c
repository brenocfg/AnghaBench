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
struct nilfs_dir_entry {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 struct page* nilfs_get_page (struct inode*,int /*<<< orphan*/ ) ; 
 struct nilfs_dir_entry* nilfs_next_entry (struct nilfs_dir_entry*) ; 
 scalar_t__ page_address (struct page*) ; 

struct nilfs_dir_entry *nilfs_dotdot(struct inode *dir, struct page **p)
{
	struct page *page = nilfs_get_page(dir, 0);
	struct nilfs_dir_entry *de = NULL;

	if (!IS_ERR(page)) {
		de = nilfs_next_entry(
			(struct nilfs_dir_entry *)page_address(page));
		*p = page;
	}
	return de;
}