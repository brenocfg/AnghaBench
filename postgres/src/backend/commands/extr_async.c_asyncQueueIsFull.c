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

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_HEAD ; 
 int QUEUE_MAX_PAGE ; 
 int QUEUE_POS_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_TAIL ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 int asyncQueuePagePrecedes (int,int) ; 

__attribute__((used)) static bool
asyncQueueIsFull(void)
{
	int			nexthead;
	int			boundary;

	/*
	 * The queue is full if creating a new head page would create a page that
	 * logically precedes the current global tail pointer, ie, the head
	 * pointer would wrap around compared to the tail.  We cannot create such
	 * a head page for fear of confusing slru.c.  For safety we round the tail
	 * pointer back to a segment boundary (compare the truncation logic in
	 * asyncQueueAdvanceTail).
	 *
	 * Note that this test is *not* dependent on how much space there is on
	 * the current head page.  This is necessary because asyncQueueAddEntries
	 * might try to create the next head page in any case.
	 */
	nexthead = QUEUE_POS_PAGE(QUEUE_HEAD) + 1;
	if (nexthead > QUEUE_MAX_PAGE)
		nexthead = 0;			/* wrap around */
	boundary = QUEUE_POS_PAGE(QUEUE_TAIL);
	boundary -= boundary % SLRU_PAGES_PER_SEGMENT;
	return asyncQueuePagePrecedes(nexthead, boundary);
}