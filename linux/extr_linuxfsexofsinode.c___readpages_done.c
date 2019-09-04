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
struct page_collect {scalar_t__ length; int nr_pages; int /*<<< orphan*/  read_4_write; struct inode* inode; struct page** pages; int /*<<< orphan*/  ios; } ;
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG2 (char*,...) ; 
 scalar_t__ PAGE_SIZE ; 
 int PAGE_WAS_NOT_IN_IO ; 
 int /*<<< orphan*/  _LLU (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int ore_check_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcol_free (struct page_collect*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int update_read_page (struct page*,int) ; 

__attribute__((used)) static int __readpages_done(struct page_collect *pcol)
{
	int i;
	u64 good_bytes;
	u64 length = 0;
	int ret = ore_check_io(pcol->ios, NULL);

	if (likely(!ret)) {
		good_bytes = pcol->length;
		ret = PAGE_WAS_NOT_IN_IO;
	} else {
		good_bytes = 0;
	}

	EXOFS_DBGMSG2("readpages_done(0x%lx) good_bytes=0x%llx"
		     " length=0x%lx nr_pages=%u\n",
		     pcol->inode->i_ino, _LLU(good_bytes), pcol->length,
		     pcol->nr_pages);

	for (i = 0; i < pcol->nr_pages; i++) {
		struct page *page = pcol->pages[i];
		struct inode *inode = page->mapping->host;
		int page_stat;

		if (inode != pcol->inode)
			continue; /* osd might add more pages at end */

		if (likely(length < good_bytes))
			page_stat = 0;
		else
			page_stat = ret;

		EXOFS_DBGMSG2("    readpages_done(0x%lx, 0x%lx) %s\n",
			  inode->i_ino, page->index,
			  page_stat ? "bad_bytes" : "good_bytes");

		ret = update_read_page(page, page_stat);
		if (!pcol->read_4_write)
			unlock_page(page);
		length += PAGE_SIZE;
	}

	pcol_free(pcol);
	EXOFS_DBGMSG2("readpages_done END\n");
	return ret;
}