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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  Dwfl ;

/* Variables and functions */
 int /*<<< orphan*/  dwfl_pid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pid_t next_thread(Dwfl *dwfl, void *arg, void **thread_argp)
{
	/* We want only single thread to be processed. */
	if (*thread_argp != NULL)
		return 0;

	*thread_argp = arg;
	return dwfl_pid(dwfl);
}