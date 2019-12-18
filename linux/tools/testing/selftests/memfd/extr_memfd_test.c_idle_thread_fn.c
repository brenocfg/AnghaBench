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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigwait (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int idle_thread_fn(void *arg)
{
	sigset_t set;
	int sig;

	/* dummy waiter; SIGTERM terminates us anyway */
	sigemptyset(&set);
	sigaddset(&set, SIGTERM);
	sigwait(&set, &sig);

	return 0;
}