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
struct panel_drv_data {int dummy; } ;

/* Variables and functions */
 int MIPID_CMD_SLEEP_IN ; 
 int MIPID_CMD_SLEEP_OUT ; 
 int /*<<< orphan*/  acx565akm_cmd (struct panel_drv_data*,int) ; 
 int /*<<< orphan*/  hw_guard_start (struct panel_drv_data*,int) ; 
 int /*<<< orphan*/  hw_guard_wait (struct panel_drv_data*) ; 

__attribute__((used)) static void set_sleep_mode(struct panel_drv_data *ddata, int on)
{
	int cmd;

	if (on)
		cmd = MIPID_CMD_SLEEP_IN;
	else
		cmd = MIPID_CMD_SLEEP_OUT;
	/*
	 * We have to keep 120msec between sleep in/out commands.
	 * (8.2.15, 8.2.16).
	 */
	hw_guard_wait(ddata);
	acx565akm_cmd(ddata, cmd);
	hw_guard_start(ddata, 120);
}