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
 int HZ ; 
 int backend_state ; 
 int /*<<< orphan*/  backend_state_wq ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void xenbus_reset_wait_for_backend(char *be, int expected)
{
	long timeout;
	timeout = wait_event_interruptible_timeout(backend_state_wq,
			backend_state == expected, 5 * HZ);
	if (timeout <= 0)
		pr_info("backend %s timed out\n", be);
}