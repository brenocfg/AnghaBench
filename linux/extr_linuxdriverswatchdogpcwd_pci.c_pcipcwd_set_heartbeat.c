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
 int /*<<< orphan*/  CMD_WRITE_WATCHDOG_TIMEOUT ; 
 int EINVAL ; 
 scalar_t__ VERBOSE ; 
 scalar_t__ debug ; 
 int heartbeat ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  send_command (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int pcipcwd_set_heartbeat(int t)
{
	int t_msb = t / 256;
	int t_lsb = t % 256;

	if ((t < 0x0001) || (t > 0xFFFF))
		return -EINVAL;

	/* Write new heartbeat to watchdog */
	send_command(CMD_WRITE_WATCHDOG_TIMEOUT, &t_msb, &t_lsb);

	heartbeat = t;
	if (debug >= VERBOSE)
		pr_debug("New heartbeat: %d\n", heartbeat);

	return 0;
}