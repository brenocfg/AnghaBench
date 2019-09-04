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
typedef  int /*<<< orphan*/  u8 ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int ziirave_firm_write_block_data (struct watchdog_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ziirave_firm_write_byte(struct watchdog_device *wdd, u8 command,
				   u8 byte, bool wait_for_ack)
{
	return ziirave_firm_write_block_data(wdd, command, 1, &byte,
					     wait_for_ack);
}