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
struct qstr {int dummy; } ;
struct page {int dummy; } ;
struct nilfs_dir_entry {int /*<<< orphan*/  inode; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct nilfs_dir_entry* nilfs_find_entry (struct inode*,struct qstr const*,struct page**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

ino_t nilfs_inode_by_name(struct inode *dir, const struct qstr *qstr)
{
	ino_t res = 0;
	struct nilfs_dir_entry *de;
	struct page *page;

	de = nilfs_find_entry(dir, qstr, &page);
	if (de) {
		res = le64_to_cpu(de->inode);
		kunmap(page);
		put_page(page);
	}
	return res;
}