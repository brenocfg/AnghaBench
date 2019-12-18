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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_io_info {struct page* encrypted_page; int /*<<< orphan*/  old_blkaddr; int /*<<< orphan*/  sbi; TYPE_2__* page; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {TYPE_1__* mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  META_MAPPING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  __GFP_NOFAIL ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_encrypted_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_flush_merged_writes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_wait_on_block_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* fscrypt_encrypt_pagecache_blocks (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static int encrypt_one_page(struct f2fs_io_info *fio)
{
	struct inode *inode = fio->page->mapping->host;
	struct page *mpage;
	gfp_t gfp_flags = GFP_NOFS;

	if (!f2fs_encrypted_file(inode))
		return 0;

	/* wait for GCed page writeback via META_MAPPING */
	f2fs_wait_on_block_writeback(inode, fio->old_blkaddr);

retry_encrypt:
	fio->encrypted_page = fscrypt_encrypt_pagecache_blocks(fio->page,
							       PAGE_SIZE, 0,
							       gfp_flags);
	if (IS_ERR(fio->encrypted_page)) {
		/* flush pending IOs and wait for a while in the ENOMEM case */
		if (PTR_ERR(fio->encrypted_page) == -ENOMEM) {
			f2fs_flush_merged_writes(fio->sbi);
			congestion_wait(BLK_RW_ASYNC, HZ/50);
			gfp_flags |= __GFP_NOFAIL;
			goto retry_encrypt;
		}
		return PTR_ERR(fio->encrypted_page);
	}

	mpage = find_lock_page(META_MAPPING(fio->sbi), fio->old_blkaddr);
	if (mpage) {
		if (PageUptodate(mpage))
			memcpy(page_address(mpage),
				page_address(fio->encrypted_page), PAGE_SIZE);
		f2fs_put_page(mpage, 1);
	}
	return 0;
}