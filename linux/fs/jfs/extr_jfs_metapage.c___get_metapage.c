#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct metapage {unsigned int logical_size; int count; unsigned long index; scalar_t__ data; scalar_t__ nohomeok; int /*<<< orphan*/  xflag; scalar_t__ flag; int /*<<< orphan*/  sb; struct page* page; } ;
struct inode {int i_blkbits; unsigned long i_size; int /*<<< orphan*/  i_sb; struct address_space* i_mapping; int /*<<< orphan*/  i_ino; } ;
struct address_space {int dummy; } ;
struct TYPE_6__ {TYPE_1__* direct_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  pagealloc; } ;
struct TYPE_4__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_PAGE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 TYPE_3__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  META_discard ; 
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long PSIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 struct metapage* alloc_metapage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  discard_metapage (struct metapage*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  free_metapage (struct metapage*) ; 
 struct page* grab_cache_page (struct address_space*,unsigned long) ; 
 int /*<<< orphan*/  insert_metapage (struct page*,struct metapage*) ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct metapage*,...) ; 
 int /*<<< orphan*/  lock_metapage (struct metapage*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_2__ mpStat ; 
 scalar_t__ page_address (struct page*) ; 
 struct metapage* page_to_mp (struct page*,unsigned long) ; 
 struct page* read_mapping_page (struct address_space*,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct metapage *__get_metapage(struct inode *inode, unsigned long lblock,
				unsigned int size, int absolute,
				unsigned long new)
{
	int l2BlocksPerPage;
	int l2bsize;
	struct address_space *mapping;
	struct metapage *mp = NULL;
	struct page *page;
	unsigned long page_index;
	unsigned long page_offset;

	jfs_info("__get_metapage: ino = %ld, lblock = 0x%lx, abs=%d",
		 inode->i_ino, lblock, absolute);

	l2bsize = inode->i_blkbits;
	l2BlocksPerPage = PAGE_SHIFT - l2bsize;
	page_index = lblock >> l2BlocksPerPage;
	page_offset = (lblock - (page_index << l2BlocksPerPage)) << l2bsize;
	if ((page_offset + size) > PAGE_SIZE) {
		jfs_err("MetaData crosses page boundary!!");
		jfs_err("lblock = %lx, size  = %d", lblock, size);
		dump_stack();
		return NULL;
	}
	if (absolute)
		mapping = JFS_SBI(inode->i_sb)->direct_inode->i_mapping;
	else {
		/*
		 * If an nfs client tries to read an inode that is larger
		 * than any existing inodes, we may try to read past the
		 * end of the inode map
		 */
		if ((lblock << inode->i_blkbits) >= inode->i_size)
			return NULL;
		mapping = inode->i_mapping;
	}

	if (new && (PSIZE == PAGE_SIZE)) {
		page = grab_cache_page(mapping, page_index);
		if (!page) {
			jfs_err("grab_cache_page failed!");
			return NULL;
		}
		SetPageUptodate(page);
	} else {
		page = read_mapping_page(mapping, page_index, NULL);
		if (IS_ERR(page) || !PageUptodate(page)) {
			jfs_err("read_mapping_page failed!");
			return NULL;
		}
		lock_page(page);
	}

	mp = page_to_mp(page, page_offset);
	if (mp) {
		if (mp->logical_size != size) {
			jfs_error(inode->i_sb,
				  "get_mp->logical_size != size\n");
			jfs_err("logical_size = %d, size = %d",
				mp->logical_size, size);
			dump_stack();
			goto unlock;
		}
		mp->count++;
		lock_metapage(mp);
		if (test_bit(META_discard, &mp->flag)) {
			if (!new) {
				jfs_error(inode->i_sb,
					  "using a discarded metapage\n");
				discard_metapage(mp);
				goto unlock;
			}
			clear_bit(META_discard, &mp->flag);
		}
	} else {
		INCREMENT(mpStat.pagealloc);
		mp = alloc_metapage(GFP_NOFS);
		if (!mp)
			goto unlock;
		mp->page = page;
		mp->sb = inode->i_sb;
		mp->flag = 0;
		mp->xflag = COMMIT_PAGE;
		mp->count = 1;
		mp->nohomeok = 0;
		mp->logical_size = size;
		mp->data = page_address(page) + page_offset;
		mp->index = lblock;
		if (unlikely(insert_metapage(page, mp))) {
			free_metapage(mp);
			goto unlock;
		}
		lock_metapage(mp);
	}

	if (new) {
		jfs_info("zeroing mp = 0x%p", mp);
		memset(mp->data, 0, PSIZE);
	}

	unlock_page(page);
	jfs_info("__get_metapage: returning = 0x%p data = 0x%p", mp, mp->data);
	return mp;

unlock:
	unlock_page(page);
	return NULL;
}