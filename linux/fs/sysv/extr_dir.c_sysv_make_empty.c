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
struct sysv_dir_entry {int /*<<< orphan*/  name; void* inode; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SYSV_DIRSIZE ; 
 int /*<<< orphan*/  SYSV_SB (int /*<<< orphan*/ ) ; 
 void* cpu_to_fs16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dir_commit_chunk (struct page*,int /*<<< orphan*/ ,int) ; 
 struct page* grab_cache_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int sysv_prepare_chunk (struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int sysv_make_empty(struct inode *inode, struct inode *dir)
{
	struct page *page = grab_cache_page(inode->i_mapping, 0);
	struct sysv_dir_entry * de;
	char *base;
	int err;

	if (!page)
		return -ENOMEM;
	err = sysv_prepare_chunk(page, 0, 2 * SYSV_DIRSIZE);
	if (err) {
		unlock_page(page);
		goto fail;
	}
	kmap(page);

	base = (char*)page_address(page);
	memset(base, 0, PAGE_SIZE);

	de = (struct sysv_dir_entry *) base;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	strcpy(de->name,".");
	de++;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), dir->i_ino);
	strcpy(de->name,"..");

	kunmap(page);
	err = dir_commit_chunk(page, 0, 2 * SYSV_DIRSIZE);
fail:
	put_page(page);
	return err;
}