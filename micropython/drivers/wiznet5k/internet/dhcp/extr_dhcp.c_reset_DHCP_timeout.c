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
 int /*<<< orphan*/  DHCP_WAIT_TIME ; 
 scalar_t__ dhcp_retry_count ; 
 scalar_t__ dhcp_tick_1s ; 
 int /*<<< orphan*/  dhcp_tick_next ; 

void reset_DHCP_timeout(void)
{
	dhcp_tick_1s = 0;
	dhcp_tick_next = DHCP_WAIT_TIME;
	dhcp_retry_count = 0;
}