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
 int SIGSEGV ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ segv_expected ; 

void signal_segv(int signum)
{
	if (segv_expected && (signum == SIGSEGV))
		_exit(0);
	_exit(1);
}