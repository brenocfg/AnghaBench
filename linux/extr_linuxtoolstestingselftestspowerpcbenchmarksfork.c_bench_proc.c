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
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  bench_fork () ; 
 int /*<<< orphan*/  bench_thread () ; 
 int /*<<< orphan*/  bench_vfork () ; 
 scalar_t__ do_fork ; 
 scalar_t__ do_vfork ; 
 int /*<<< orphan*/  sigalrm_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *bench_proc(void *arg)
{
	signal(SIGALRM, sigalrm_handler);
	alarm(1);

	if (do_fork)
		bench_fork();
	else if (do_vfork)
		bench_vfork();
	else
		bench_thread();

	return NULL;
}