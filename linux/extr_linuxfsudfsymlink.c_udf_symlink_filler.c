#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {unsigned char* i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenEAttr; int /*<<< orphan*/  i_data_sem; TYPE_2__ i_ext; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {scalar_t__ i_size; TYPE_3__* i_sb; } ;
struct file {int dummy; } ;
struct buffer_head {unsigned char* b_data; } ;
struct TYPE_7__ {scalar_t__ s_blocksize; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int ENAMETOOLONG ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned char* page_address (struct page*) ; 
 struct buffer_head* sb_bread (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_block_map (struct inode*,int /*<<< orphan*/ ) ; 
 int udf_pc_to_char (TYPE_3__*,unsigned char*,scalar_t__,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_symlink_filler(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head *bh = NULL;
	unsigned char *symlink;
	int err;
	unsigned char *p = page_address(page);
	struct udf_inode_info *iinfo;
	uint32_t pos;

	/* We don't support symlinks longer than one block */
	if (inode->i_size > inode->i_sb->s_blocksize) {
		err = -ENAMETOOLONG;
		goto out_unmap;
	}

	iinfo = UDF_I(inode);
	pos = udf_block_map(inode, 0);

	down_read(&iinfo->i_data_sem);
	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
		symlink = iinfo->i_ext.i_data + iinfo->i_lenEAttr;
	} else {
		bh = sb_bread(inode->i_sb, pos);

		if (!bh) {
			err = -EIO;
			goto out_unlock_inode;
		}

		symlink = bh->b_data;
	}

	err = udf_pc_to_char(inode->i_sb, symlink, inode->i_size, p, PAGE_SIZE);
	brelse(bh);
	if (err)
		goto out_unlock_inode;

	up_read(&iinfo->i_data_sem);
	SetPageUptodate(page);
	unlock_page(page);
	return 0;

out_unlock_inode:
	up_read(&iinfo->i_data_sem);
	SetPageError(page);
out_unmap:
	unlock_page(page);
	return err;
}