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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 unsigned int SIGCHLD ; 
 int STACK_SIZE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ clone (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_thread_fn ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static pid_t spawn_idle_thread(unsigned int flags)
{
	uint8_t *stack;
	pid_t pid;

	stack = malloc(STACK_SIZE);
	if (!stack) {
		printf("malloc(STACK_SIZE) failed: %m\n");
		abort();
	}

	pid = clone(idle_thread_fn,
		    stack + STACK_SIZE,
		    SIGCHLD | flags,
		    NULL);
	if (pid < 0) {
		printf("clone() failed: %m\n");
		abort();
	}

	return pid;
}