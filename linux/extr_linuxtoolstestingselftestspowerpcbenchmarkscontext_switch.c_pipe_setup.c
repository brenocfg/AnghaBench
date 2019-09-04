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
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_fd1 ; 
 int /*<<< orphan*/  pipe_fd2 ; 

__attribute__((used)) static void pipe_setup(int cpu1, int cpu2)
{
	if (pipe(pipe_fd1) || pipe(pipe_fd2))
		exit(1);
}