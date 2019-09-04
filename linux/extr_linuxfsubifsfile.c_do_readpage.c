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
struct ubifs_info {int dummy; } ;
struct ubifs_data_node {int /*<<< orphan*/  size; } ;
struct page {unsigned int index; int /*<<< orphan*/  flags; TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_2__* i_sb; } ;
typedef  int loff_t ;
struct TYPE_4__ {struct ubifs_info* s_fs_info; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageChecked (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  SetPageChecked (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int UBIFS_BLOCKS_PER_PAGE ; 
 unsigned int UBIFS_BLOCKS_PER_PAGE_SHIFT ; 
 int UBIFS_BLOCK_SHIFT ; 
 int UBIFS_BLOCK_SIZE ; 
 int /*<<< orphan*/  UBIFS_MAX_DATA_NODE_SZ ; 
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_data_node*) ; 
 struct ubifs_data_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int read_block (struct inode*,void*,unsigned int,struct ubifs_data_node*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_readpage(struct page *page)
{
	void *addr;
	int err = 0, i;
	unsigned int block, beyond;
	struct ubifs_data_node *dn;
	struct inode *inode = page->mapping->host;
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	loff_t i_size = i_size_read(inode);

	dbg_gen("ino %lu, pg %lu, i_size %lld, flags %#lx",
		inode->i_ino, page->index, i_size, page->flags);
	ubifs_assert(c, !PageChecked(page));
	ubifs_assert(c, !PagePrivate(page));

	addr = kmap(page);

	block = page->index << UBIFS_BLOCKS_PER_PAGE_SHIFT;
	beyond = (i_size + UBIFS_BLOCK_SIZE - 1) >> UBIFS_BLOCK_SHIFT;
	if (block >= beyond) {
		/* Reading beyond inode */
		SetPageChecked(page);
		memset(addr, 0, PAGE_SIZE);
		goto out;
	}

	dn = kmalloc(UBIFS_MAX_DATA_NODE_SZ, GFP_NOFS);
	if (!dn) {
		err = -ENOMEM;
		goto error;
	}

	i = 0;
	while (1) {
		int ret;

		if (block >= beyond) {
			/* Reading beyond inode */
			err = -ENOENT;
			memset(addr, 0, UBIFS_BLOCK_SIZE);
		} else {
			ret = read_block(inode, addr, block, dn);
			if (ret) {
				err = ret;
				if (err != -ENOENT)
					break;
			} else if (block + 1 == beyond) {
				int dlen = le32_to_cpu(dn->size);
				int ilen = i_size & (UBIFS_BLOCK_SIZE - 1);

				if (ilen && ilen < dlen)
					memset(addr + ilen, 0, dlen - ilen);
			}
		}
		if (++i >= UBIFS_BLOCKS_PER_PAGE)
			break;
		block += 1;
		addr += UBIFS_BLOCK_SIZE;
	}
	if (err) {
		struct ubifs_info *c = inode->i_sb->s_fs_info;
		if (err == -ENOENT) {
			/* Not found, so it must be a hole */
			SetPageChecked(page);
			dbg_gen("hole");
			goto out_free;
		}
		ubifs_err(c, "cannot read page %lu of inode %lu, error %d",
			  page->index, inode->i_ino, err);
		goto error;
	}

out_free:
	kfree(dn);
out:
	SetPageUptodate(page);
	ClearPageError(page);
	flush_dcache_page(page);
	kunmap(page);
	return 0;

error:
	kfree(dn);
	ClearPageUptodate(page);
	SetPageError(page);
	flush_dcache_page(page);
	kunmap(page);
	return err;
}