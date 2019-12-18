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
 size_t READ ; 
 int /*<<< orphan*/  SIGALRM ; 
 size_t WRITE ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c ; 
 int iterations ; 
 int /*<<< orphan*/ * pipe_fd1 ; 
 int /*<<< orphan*/ * pipe_fd2 ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigalrm_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch () ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *pipe_thread1(void *arg)
{
	signal(SIGALRM, sigalrm_handler);
	alarm(1);

	while (1) {
		assert(read(pipe_fd1[READ], &c, 1) == 1);
		touch();

		assert(write(pipe_fd2[WRITE], &c, 1) == 1);
		touch();

		iterations += 2;
	}

	return NULL;
}