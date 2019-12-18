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
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct page {int dummy; } ;
struct f2fs_inode {int /*<<< orphan*/  i_name; int /*<<< orphan*/  i_namelen; } ;

/* Variables and functions */
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static void init_dent_inode(const struct qstr *name, struct page *ipage)
{
	struct f2fs_inode *ri;

	f2fs_wait_on_page_writeback(ipage, NODE, true, true);

	/* copy name info. to this inode page */
	ri = F2FS_INODE(ipage);
	ri->i_namelen = cpu_to_le32(name->len);
	memcpy(ri->i_name, name->name, name->len);
	set_page_dirty(ipage);
}