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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BRIN_PAGETYPE_REGULAR ; 
 int /*<<< orphan*/  BRIN_elog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordPageWithFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  br_page_get_freespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_page_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_newpage_buffer (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
brin_initialize_empty_new_buffer(Relation idxrel, Buffer buffer)
{
	Page		page;

	BRIN_elog((DEBUG2,
			   "brin_initialize_empty_new_buffer: initializing blank page %u",
			   BufferGetBlockNumber(buffer)));

	START_CRIT_SECTION();
	page = BufferGetPage(buffer);
	brin_page_init(page, BRIN_PAGETYPE_REGULAR);
	MarkBufferDirty(buffer);
	log_newpage_buffer(buffer, true);
	END_CRIT_SECTION();

	/*
	 * We update the FSM for this page, but this is not WAL-logged.  This is
	 * acceptable because VACUUM will scan the index and update the FSM with
	 * pages whose FSM records were forgotten in a crash.
	 */
	RecordPageWithFreeSpace(idxrel, BufferGetBlockNumber(buffer),
							br_page_get_freespace(page));
}