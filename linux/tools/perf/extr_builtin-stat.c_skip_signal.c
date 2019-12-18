#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ interval; } ;

/* Variables and functions */
 int child_pid ; 
 int done ; 
 int signr ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static void skip_signal(int signo)
{
	if ((child_pid == -1) || stat_config.interval)
		done = 1;

	signr = signo;
	/*
	 * render child_pid harmless
	 * won't send SIGTERM to a random
	 * process in case of race condition
	 * and fast PID recycling
	 */
	child_pid = -1;
}