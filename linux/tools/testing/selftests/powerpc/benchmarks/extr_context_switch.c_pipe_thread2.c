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
 size_t WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c ; 
 int /*<<< orphan*/ * pipe_fd1 ; 
 int /*<<< orphan*/ * pipe_fd2 ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  touch () ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *pipe_thread2(void *arg)
{
	while (1) {
		assert(write(pipe_fd1[WRITE], &c, 1) == 1);
		touch();

		assert(read(pipe_fd2[READ], &c, 1) == 1);
		touch();
	}

	return NULL;
}