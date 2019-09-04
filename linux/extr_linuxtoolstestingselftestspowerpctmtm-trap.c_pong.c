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
 int /*<<< orphan*/  exit_from_pong ; 
 int /*<<< orphan*/  sched_yield () ; 

void *pong(void *not_used)
{
	while (!exit_from_pong)
		/*
		 * Induce context switches on ping() thread
		 * until ping() finishes its job and signs
		 * to exit from this loop.
		 */
		sched_yield();

	return NULL;
}