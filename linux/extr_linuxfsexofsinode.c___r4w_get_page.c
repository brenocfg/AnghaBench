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
typedef  scalar_t__ u64 ;
struct page_collect {struct page* that_locked_page; TYPE_1__* inode; } ;
struct page {scalar_t__ index; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXOFS_DBGMSG2 (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ PAGE_SIZE ; 
 int PageUptodate (struct page*) ; 
 struct page* ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _LLU (scalar_t__) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,scalar_t__) ; 
 struct page* find_or_create_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static struct page *__r4w_get_page(void *priv, u64 offset, bool *uptodate)
{
	struct page_collect *pcol = priv;
	pgoff_t index = offset / PAGE_SIZE;

	if (!pcol->that_locked_page ||
	    (pcol->that_locked_page->index != index)) {
		struct page *page;
		loff_t i_size = i_size_read(pcol->inode);

		if (offset >= i_size) {
			*uptodate = true;
			EXOFS_DBGMSG2("offset >= i_size index=0x%lx\n", index);
			return ZERO_PAGE(0);
		}

		page =  find_get_page(pcol->inode->i_mapping, index);
		if (!page) {
			page = find_or_create_page(pcol->inode->i_mapping,
						   index, GFP_NOFS);
			if (unlikely(!page)) {
				EXOFS_DBGMSG("grab_cache_page Failed "
					"index=0x%llx\n", _LLU(index));
				return NULL;
			}
			unlock_page(page);
		}
		*uptodate = PageUptodate(page);
		EXOFS_DBGMSG2("index=0x%lx uptodate=%d\n", index, *uptodate);
		return page;
	} else {
		EXOFS_DBGMSG2("YES that_locked_page index=0x%lx\n",
			     pcol->that_locked_page->index);
		*uptodate = true;
		return pcol->that_locked_page;
	}
}