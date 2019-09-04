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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EEEPC_EC_FAN_CTRL ; 
 int EEEPC_EC_FAN_CTRL_BIT ; 
 int EEEPC_FAN_CTRL_AUTO ; 
 int EEEPC_FAN_CTRL_MANUAL ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int eeepc_get_fan_ctrl(void)
{
	u8 value = 0;

	ec_read(EEEPC_EC_FAN_CTRL, &value);
	if (value & EEEPC_EC_FAN_CTRL_BIT)
		return EEEPC_FAN_CTRL_MANUAL;
	else
		return EEEPC_FAN_CTRL_AUTO;
}