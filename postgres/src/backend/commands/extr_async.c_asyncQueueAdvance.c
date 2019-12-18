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
typedef  int /*<<< orphan*/  QueuePosition ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AsyncQueueEntryEmptySize ; 
 int QUEUEALIGN (int /*<<< orphan*/ ) ; 
 int QUEUE_MAX_PAGE ; 
 int QUEUE_PAGESIZE ; 
 int QUEUE_POS_OFFSET (int /*<<< orphan*/  volatile) ; 
 int QUEUE_POS_PAGE (int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  SET_QUEUE_POS (int /*<<< orphan*/  volatile,int,int) ; 

__attribute__((used)) static bool
asyncQueueAdvance(volatile QueuePosition *position, int entryLength)
{
	int			pageno = QUEUE_POS_PAGE(*position);
	int			offset = QUEUE_POS_OFFSET(*position);
	bool		pageJump = false;

	/*
	 * Move to the next writing position: First jump over what we have just
	 * written or read.
	 */
	offset += entryLength;
	Assert(offset <= QUEUE_PAGESIZE);

	/*
	 * In a second step check if another entry can possibly be written to the
	 * page. If so, stay here, we have reached the next position. If not, then
	 * we need to move on to the next page.
	 */
	if (offset + QUEUEALIGN(AsyncQueueEntryEmptySize) > QUEUE_PAGESIZE)
	{
		pageno++;
		if (pageno > QUEUE_MAX_PAGE)
			pageno = 0;			/* wrap around */
		offset = 0;
		pageJump = true;
	}

	SET_QUEUE_POS(*position, pageno, offset);
	return pageJump;
}