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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct coda_inode_info {int /*<<< orphan*/  c_fid; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct coda_inode_info* ITOC (struct inode*) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int venus_readlink (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int*) ; 

__attribute__((used)) static int coda_symlink_filler(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	int error;
	struct coda_inode_info *cii;
	unsigned int len = PAGE_SIZE;
	char *p = page_address(page);

	cii = ITOC(inode);

	error = venus_readlink(inode->i_sb, &cii->c_fid, p, &len);
	if (error)
		goto fail;
	SetPageUptodate(page);
	unlock_page(page);
	return 0;

fail:
	SetPageError(page);
	unlock_page(page);
	return error;
}