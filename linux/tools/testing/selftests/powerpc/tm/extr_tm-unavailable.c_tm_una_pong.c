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
 scalar_t__ DEBUG ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  sleep (int) ; 

void *tm_una_pong(void *not_used)
{
	/* Wait thread get its name "pong". */
	if (DEBUG)
		sleep(1);

	/* Classed as an interactive-like thread. */
	while (1)
		sched_yield();
}