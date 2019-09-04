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
typedef  scalar_t__ u64 ;
struct page_collect {scalar_t__ length; int nr_pages; struct inode* inode; struct page** pages; TYPE_1__* sbi; } ;
struct page {int /*<<< orphan*/  index; TYPE_2__* mapping; } ;
struct ore_io_state {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {struct inode* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_curr_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG2 (char*,...) ; 
 scalar_t__ PAGE_SIZE ; 
 int PAGE_WAS_NOT_IN_IO ; 
 int /*<<< orphan*/  _LLU (scalar_t__) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct page_collect*) ; 
 scalar_t__ likely (int) ; 
 int ore_check_io (struct ore_io_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcol_free (struct page_collect*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_write_page (struct page*,int) ; 

__attribute__((used)) static void writepages_done(struct ore_io_state *ios, void *p)
{
	struct page_collect *pcol = p;
	int i;
	u64  good_bytes;
	u64  length = 0;
	int ret = ore_check_io(ios, NULL);

	atomic_dec(&pcol->sbi->s_curr_pending);

	if (likely(!ret)) {
		good_bytes = pcol->length;
		ret = PAGE_WAS_NOT_IN_IO;
	} else {
		good_bytes = 0;
	}

	EXOFS_DBGMSG2("writepages_done(0x%lx) good_bytes=0x%llx"
		     " length=0x%lx nr_pages=%u\n",
		     pcol->inode->i_ino, _LLU(good_bytes), pcol->length,
		     pcol->nr_pages);

	for (i = 0; i < pcol->nr_pages; i++) {
		struct page *page = pcol->pages[i];
		struct inode *inode = page->mapping->host;
		int page_stat;

		if (inode != pcol->inode)
			continue; /* osd might add more pages to a bio */

		if (likely(length < good_bytes))
			page_stat = 0;
		else
			page_stat = ret;

		update_write_page(page, page_stat);
		unlock_page(page);
		EXOFS_DBGMSG2("    writepages_done(0x%lx, 0x%lx) status=%d\n",
			     inode->i_ino, page->index, page_stat);

		length += PAGE_SIZE;
	}

	pcol_free(pcol);
	kfree(pcol);
	EXOFS_DBGMSG2("writepages_done END\n");
}