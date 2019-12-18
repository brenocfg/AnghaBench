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
struct sysv_dir_entry {int /*<<< orphan*/  inode; } ;
struct page {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYSV_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  fs16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sysv_dir_entry* sysv_find_entry (struct dentry*,struct page**) ; 

ino_t sysv_inode_by_name(struct dentry *dentry)
{
	struct page *page;
	struct sysv_dir_entry *de = sysv_find_entry (dentry, &page);
	ino_t res = 0;
	
	if (de) {
		res = fs16_to_cpu(SYSV_SB(dentry->d_sb), de->inode);
		dir_put_page(page);
	}
	return res;
}