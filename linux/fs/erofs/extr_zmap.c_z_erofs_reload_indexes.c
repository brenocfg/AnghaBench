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
struct z_erofs_maprecorder {int /*<<< orphan*/ * kaddr; struct erofs_map_blocks* map; TYPE_1__* inode; } ;
struct super_block {int dummy; } ;
struct page {int /*<<< orphan*/  index; } ;
struct erofs_map_blocks {struct page* mpage; } ;
typedef  int /*<<< orphan*/  erofs_blk_t ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 struct page* erofs_get_meta_page (struct super_block* const,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int z_erofs_reload_indexes(struct z_erofs_maprecorder *m,
				  erofs_blk_t eblk)
{
	struct super_block *const sb = m->inode->i_sb;
	struct erofs_map_blocks *const map = m->map;
	struct page *mpage = map->mpage;

	if (mpage) {
		if (mpage->index == eblk) {
			if (!m->kaddr)
				m->kaddr = kmap_atomic(mpage);
			return 0;
		}

		if (m->kaddr) {
			kunmap_atomic(m->kaddr);
			m->kaddr = NULL;
		}
		put_page(mpage);
	}

	mpage = erofs_get_meta_page(sb, eblk);
	if (IS_ERR(mpage)) {
		map->mpage = NULL;
		return PTR_ERR(mpage);
	}
	m->kaddr = kmap_atomic(mpage);
	unlock_page(mpage);
	map->mpage = mpage;
	return 0;
}