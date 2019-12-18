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
struct inode {int dummy; } ;
struct f2fs_dir_entry {int /*<<< orphan*/  ino; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 struct f2fs_dir_entry* f2fs_find_entry (struct inode*,struct qstr const*,struct page**) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

ino_t f2fs_inode_by_name(struct inode *dir, const struct qstr *qstr,
							struct page **page)
{
	ino_t res = 0;
	struct f2fs_dir_entry *de;

	de = f2fs_find_entry(dir, qstr, page);
	if (de) {
		res = le32_to_cpu(de->ino);
		f2fs_put_page(*page, 0);
	}

	return res;
}