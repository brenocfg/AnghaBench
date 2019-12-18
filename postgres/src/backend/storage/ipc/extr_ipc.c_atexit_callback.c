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
 int /*<<< orphan*/  proc_exit_prepare (int) ; 

__attribute__((used)) static void
atexit_callback(void)
{
	/* Clean up everything that must be cleaned up */
	/* ... too bad we don't know the real exit code ... */
	proc_exit_prepare(-1);
}