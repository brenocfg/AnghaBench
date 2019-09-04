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
struct TYPE_2__ {int b_srp_done; scalar_t__ power_up; scalar_t__ b_bus_req; } ;
struct ci_hdrc {int /*<<< orphan*/  dev; TYPE_1__ fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTGSC_HABA ; 
 int /*<<< orphan*/  hw_write_otgsc (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b_data_pls_tmout(struct ci_hdrc *ci)
{
	ci->fsm.b_srp_done = 1;
	ci->fsm.b_bus_req = 0;
	if (ci->fsm.power_up)
		ci->fsm.power_up = 0;
	hw_write_otgsc(ci, OTGSC_HABA, 0);
	pm_runtime_put(ci->dev);
	return 0;
}