#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_2__* mapping; } ;
struct TYPE_3__ {scalar_t__ i_symlink; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_fast_symlink_chars (int /*<<< orphan*/ ) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 size_t strnlen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ocfs2_fast_symlink_readpage(struct file *unused, struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head *bh = NULL;
	int status = ocfs2_read_inode_block(inode, &bh);
	struct ocfs2_dinode *fe;
	const char *link;
	void *kaddr;
	size_t len;

	if (status < 0) {
		mlog_errno(status);
		return status;
	}

	fe = (struct ocfs2_dinode *) bh->b_data;
	link = (char *) fe->id2.i_symlink;
	/* will be less than a page size */
	len = strnlen(link, ocfs2_fast_symlink_chars(inode->i_sb));
	kaddr = kmap_atomic(page);
	memcpy(kaddr, link, len + 1);
	kunmap_atomic(kaddr);
	SetPageUptodate(page);
	unlock_page(page);
	brelse(bh);
	return 0;
}