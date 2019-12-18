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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  sched_yield () ; 
 scalar_t__ segv_wait ; 

__attribute__((used)) static void segv_handler(int signo, siginfo_t *info, void *extra)
{
	while (segv_wait) {
		sched_yield();
	}

}