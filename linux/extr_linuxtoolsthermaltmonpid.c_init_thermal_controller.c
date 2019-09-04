#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double kp; double ki; double kd; int /*<<< orphan*/  t_target; int /*<<< orphan*/  ts; } ;

/* Variables and functions */
 TYPE_1__ p_param ; 
 int /*<<< orphan*/  target_temp_user ; 
 int /*<<< orphan*/  ticktime ; 

int init_thermal_controller(void)
{
	int ret = 0;

	/* init pid params */
	p_param.ts = ticktime;
	/* TODO: get it from TUI tuning tab */
	p_param.kp = .36;
	p_param.ki = 5.0;
	p_param.kd = 0.19;

	p_param.t_target = target_temp_user;

	return ret;
}