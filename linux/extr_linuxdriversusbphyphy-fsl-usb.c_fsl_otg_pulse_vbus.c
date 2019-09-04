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
struct TYPE_2__ {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  b_vbus_pulse_tmr ; 
 int /*<<< orphan*/  fsl_otg_add_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_otg_chrg_vbus (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* fsl_otg_dev ; 
 scalar_t__ srp_wait_done ; 

void fsl_otg_pulse_vbus(void)
{
	srp_wait_done = 0;
	fsl_otg_chrg_vbus(&fsl_otg_dev->fsm, 1);
	/* start the timer to end vbus charge */
	fsl_otg_add_timer(&fsl_otg_dev->fsm, b_vbus_pulse_tmr);
}