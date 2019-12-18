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
struct page {int dummy; } ;
struct journal_head {int /*<<< orphan*/  b_triggers; int /*<<< orphan*/  b_frozen_triggers; int /*<<< orphan*/  b_frozen_data; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; struct page* b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  J_EXPECT_JH (struct journal_head*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_buffer_frozen_trigger (struct journal_head*,char*,int /*<<< orphan*/ ) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jbd2_freeze_jh_data(struct journal_head *jh)
{
	struct page *page;
	int offset;
	char *source;
	struct buffer_head *bh = jh2bh(jh);

	J_EXPECT_JH(jh, buffer_uptodate(bh), "Possible IO failure.\n");
	page = bh->b_page;
	offset = offset_in_page(bh->b_data);
	source = kmap_atomic(page);
	/* Fire data frozen trigger just before we copy the data */
	jbd2_buffer_frozen_trigger(jh, source + offset, jh->b_triggers);
	memcpy(jh->b_frozen_data, source + offset, bh->b_size);
	kunmap_atomic(source);

	/*
	 * Now that the frozen data is saved off, we need to store any matching
	 * triggers.
	 */
	jh->b_frozen_triggers = jh->b_triggers;
}