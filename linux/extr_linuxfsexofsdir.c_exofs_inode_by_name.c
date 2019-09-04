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
struct exofs_dir_entry {int /*<<< orphan*/  inode_no; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 struct exofs_dir_entry* exofs_find_entry (struct inode*,struct dentry*,struct page**) ; 
 int /*<<< orphan*/  exofs_put_page (struct page*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

ino_t exofs_inode_by_name(struct inode *dir, struct dentry *dentry)
{
	ino_t res = 0;
	struct exofs_dir_entry *de;
	struct page *page;

	de = exofs_find_entry(dir, dentry, &page);
	if (de) {
		res = le64_to_cpu(de->inode_no);
		exofs_put_page(page);
	}
	return res;
}