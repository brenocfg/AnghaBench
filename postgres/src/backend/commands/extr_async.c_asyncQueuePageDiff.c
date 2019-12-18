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
 int /*<<< orphan*/  Assert (int) ; 
 int QUEUE_MAX_PAGE ; 

__attribute__((used)) static int
asyncQueuePageDiff(int p, int q)
{
	int			diff;

	/*
	 * We have to compare modulo (QUEUE_MAX_PAGE+1)/2.  Both inputs should be
	 * in the range 0..QUEUE_MAX_PAGE.
	 */
	Assert(p >= 0 && p <= QUEUE_MAX_PAGE);
	Assert(q >= 0 && q <= QUEUE_MAX_PAGE);

	diff = p - q;
	if (diff >= ((QUEUE_MAX_PAGE + 1) / 2))
		diff -= QUEUE_MAX_PAGE + 1;
	else if (diff < -((QUEUE_MAX_PAGE + 1) / 2))
		diff += QUEUE_MAX_PAGE + 1;
	return diff;
}