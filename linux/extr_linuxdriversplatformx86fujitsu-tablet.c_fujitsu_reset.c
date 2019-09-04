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
 int /*<<< orphan*/  fujitsu_ack () ; 
 int /*<<< orphan*/  fujitsu_send_state () ; 
 int fujitsu_status () ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void fujitsu_reset(void)
{
	int timeout = 50;

	fujitsu_ack();

	while ((fujitsu_status() & 0x02) && (--timeout))
		msleep(20);

	fujitsu_send_state();
}