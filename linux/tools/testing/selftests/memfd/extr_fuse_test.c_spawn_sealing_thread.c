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
 int CLONE_FILES ; 
 int CLONE_FS ; 
 int CLONE_VM ; 
 int SIGCHLD ; 
 int STACK_SIZE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ clone (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sealing_thread_fn ; 

__attribute__((used)) static pid_t spawn_sealing_thread(void)
{
	uint8_t *stack;
	pid_t pid;

	stack = malloc(STACK_SIZE);
	if (!stack) {
		printf("malloc(STACK_SIZE) failed: %m\n");
		abort();
	}

	pid = clone(sealing_thread_fn,
		    stack + STACK_SIZE,
		    SIGCHLD | CLONE_FILES | CLONE_FS | CLONE_VM,
		    NULL);
	if (pid < 0) {
		printf("clone() failed: %m\n");
		abort();
	}

	return pid;
}