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
typedef  union pipe {int dummy; } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  notify_parent (union pipe) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_parent (union pipe) ; 

__attribute__((used)) static int eat_cpu_child(union pipe read_pipe, union pipe write_pipe)
{
	volatile int i = 0;

	/*
	 * We are just here to eat cpu and die. So make sure we can be killed,
	 * and also don't do any custom SIGTERM handling.
	 */
	signal(SIGTERM, SIG_DFL);

	notify_parent(write_pipe);
	wait_for_parent(read_pipe);

	/* Soak up cpu forever */
	while (1) i++;

	return 0;
}