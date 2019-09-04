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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf3 (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  pkey_assert (int) ; 

void become_child(void)
{
	pid_t forkret;

	forkret = fork();
	pkey_assert(forkret >= 0);
	dprintf3("[%d] fork() ret: %d\n", getpid(), forkret);

	if (!forkret) {
		/* in the child */
		return;
	}
	exit(0);
}