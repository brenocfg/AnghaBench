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

__attribute__((used)) static double
asyncQueueUsage(void)
{
	int			headPage = QUEUE_POS_PAGE(QUEUE_HEAD);
	int			tailPage = QUEUE_POS_PAGE(QUEUE_TAIL);
	int			occupied;

	occupied = headPage - tailPage;

	if (occupied == 0)
		return (double) 0;		/* fast exit for common case */

	if (occupied < 0)
	{
		/* head has wrapped around, tail not yet */
		occupied += QUEUE_MAX_PAGE + 1;
	}

	return (double) occupied / (double) ((QUEUE_MAX_PAGE + 1) / 2);
}