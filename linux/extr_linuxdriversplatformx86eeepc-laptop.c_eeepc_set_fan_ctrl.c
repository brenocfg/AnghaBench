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

/* Variables and functions */
 int /*<<< orphan*/  EEEPC_EC_FAN_CTRL ; 
 int /*<<< orphan*/  EEEPC_EC_FAN_CTRL_BIT ; 
 int EEEPC_FAN_CTRL_MANUAL ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eeepc_set_fan_ctrl(int manual)
{
	u8 value = 0;

	ec_read(EEEPC_EC_FAN_CTRL, &value);
	if (manual == EEEPC_FAN_CTRL_MANUAL)
		value |= EEEPC_EC_FAN_CTRL_BIT;
	else
		value &= ~EEEPC_EC_FAN_CTRL_BIT;
	ec_write(EEEPC_EC_FAN_CTRL, value);
}