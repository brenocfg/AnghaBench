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
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EXT4_JOURNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ PageChecked (struct page*) ; 
 int jbd2_journal_try_to_free_buffers (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_releasepage (struct page*) ; 
 int try_to_free_buffers (struct page*) ; 

__attribute__((used)) static int ext4_releasepage(struct page *page, gfp_t wait)
{
	journal_t *journal = EXT4_JOURNAL(page->mapping->host);

	trace_ext4_releasepage(page);

	/* Page has dirty journalled data -> cannot release */
	if (PageChecked(page))
		return 0;
	if (journal)
		return jbd2_journal_try_to_free_buffers(journal, page, wait);
	else
		return try_to_free_buffers(page);
}