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
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/ * EXT4_JOURNAL (int /*<<< orphan*/ ) ; 
 unsigned int PAGE_SIZE ; 
 int jbd2_journal_invalidatepage (int /*<<< orphan*/ *,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  trace_ext4_journalled_invalidatepage (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static int __ext4_journalled_invalidatepage(struct page *page,
					    unsigned int offset,
					    unsigned int length)
{
	journal_t *journal = EXT4_JOURNAL(page->mapping->host);

	trace_ext4_journalled_invalidatepage(page, offset, length);

	/*
	 * If it's a full truncate we just forget about the pending dirtying
	 */
	if (offset == 0 && length == PAGE_SIZE)
		ClearPageChecked(page);

	return jbd2_journal_invalidatepage(journal, page, offset, length);
}