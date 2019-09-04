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
struct minix_sb_info {int dummy; } ;
struct minix_dir_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 struct page* dir_get_page (struct inode*,int /*<<< orphan*/ ) ; 
 struct minix_dir_entry* minix_next_entry (int /*<<< orphan*/ ,struct minix_sb_info*) ; 
 struct minix_sb_info* minix_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

struct minix_dir_entry * minix_dotdot (struct inode *dir, struct page **p)
{
	struct page *page = dir_get_page(dir, 0);
	struct minix_sb_info *sbi = minix_sb(dir->i_sb);
	struct minix_dir_entry *de = NULL;

	if (!IS_ERR(page)) {
		de = minix_next_entry(page_address(page), sbi);
		*p = page;
	}
	return de;
}