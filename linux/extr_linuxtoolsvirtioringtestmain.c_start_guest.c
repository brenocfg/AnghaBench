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
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_guest () ; 
 int /*<<< orphan*/  set_affinity (void*) ; 

void *start_guest(void *arg)
{
	set_affinity(arg);
	run_guest();
	pthread_exit(NULL);
}