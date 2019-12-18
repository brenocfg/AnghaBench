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
struct page {struct address_space* mapping; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int op_flags; int is_por; struct page* page; int /*<<< orphan*/ * encrypted_page; int /*<<< orphan*/  new_blkaddr; int /*<<< orphan*/  old_blkaddr; int /*<<< orphan*/  op; int /*<<< orphan*/  type; struct f2fs_sb_info* sbi; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int EIO ; 
 struct page* ERR_PTR (int) ; 
 int /*<<< orphan*/  META ; 
 struct address_space* META_MAPPING (struct f2fs_sb_info*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* f2fs_grab_cache_page (struct address_space*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int f2fs_submit_page_bio (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct page *__get_meta_page(struct f2fs_sb_info *sbi, pgoff_t index,
							bool is_meta)
{
	struct address_space *mapping = META_MAPPING(sbi);
	struct page *page;
	struct f2fs_io_info fio = {
		.sbi = sbi,
		.type = META,
		.op = REQ_OP_READ,
		.op_flags = REQ_META | REQ_PRIO,
		.old_blkaddr = index,
		.new_blkaddr = index,
		.encrypted_page = NULL,
		.is_por = !is_meta,
	};
	int err;

	if (unlikely(!is_meta))
		fio.op_flags &= ~REQ_META;
repeat:
	page = f2fs_grab_cache_page(mapping, index, false);
	if (!page) {
		cond_resched();
		goto repeat;
	}
	if (PageUptodate(page))
		goto out;

	fio.page = page;

	err = f2fs_submit_page_bio(&fio);
	if (err) {
		f2fs_put_page(page, 1);
		return ERR_PTR(err);
	}

	lock_page(page);
	if (unlikely(page->mapping != mapping)) {
		f2fs_put_page(page, 1);
		goto repeat;
	}

	if (unlikely(!PageUptodate(page))) {
		f2fs_put_page(page, 1);
		return ERR_PTR(-EIO);
	}
out:
	return page;
}