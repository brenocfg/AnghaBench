#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct fnode {int dummy; } ;
struct file {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  hpfs_lock (int /*<<< orphan*/ ) ; 
 struct fnode* hpfs_map_fnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int hpfs_read_ea (int /*<<< orphan*/ ,struct fnode*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_unlock (int /*<<< orphan*/ ) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int hpfs_symlink_readpage(struct file *file, struct page *page)
{
	char *link = page_address(page);
	struct inode *i = page->mapping->host;
	struct fnode *fnode;
	struct buffer_head *bh;
	int err;

	err = -EIO;
	hpfs_lock(i->i_sb);
	if (!(fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh)))
		goto fail;
	err = hpfs_read_ea(i->i_sb, fnode, "SYMLINK", link, PAGE_SIZE);
	brelse(bh);
	if (err)
		goto fail;
	hpfs_unlock(i->i_sb);
	SetPageUptodate(page);
	unlock_page(page);
	return 0;

fail:
	hpfs_unlock(i->i_sb);
	SetPageError(page);
	unlock_page(page);
	return err;
}