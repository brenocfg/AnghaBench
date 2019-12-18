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
struct inode {int dummy; } ;
struct ext2_dir_entry_2 {int dummy; } ;
typedef  struct ext2_dir_entry_2 ext2_dirent ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 struct page* ext2_get_page (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ext2_dir_entry_2* ext2_next_entry (struct ext2_dir_entry_2*) ; 
 scalar_t__ page_address (struct page*) ; 

struct ext2_dir_entry_2 * ext2_dotdot (struct inode *dir, struct page **p)
{
	struct page *page = ext2_get_page(dir, 0, 0);
	ext2_dirent *de = NULL;

	if (!IS_ERR(page)) {
		de = ext2_next_entry((ext2_dirent *) page_address(page));
		*p = page;
	}
	return de;
}