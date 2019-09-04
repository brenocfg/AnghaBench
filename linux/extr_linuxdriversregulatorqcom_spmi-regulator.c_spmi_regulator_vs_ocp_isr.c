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
struct spmi_regulator {int ocp_count; int ocp_max_retries; int /*<<< orphan*/  dev; int /*<<< orphan*/  ocp_retry_delay_ms; int /*<<< orphan*/  ocp_work; int /*<<< orphan*/  vs_enable_time; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SPMI_VS_OCP_FALL_DELAY_US ; 
 scalar_t__ SPMI_VS_OCP_FAULT_DELAY_US ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spmi_regulator_vs_clear_ocp (struct spmi_regulator*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t spmi_regulator_vs_ocp_isr(int irq, void *data)
{
	struct spmi_regulator *vreg = data;
	ktime_t ocp_irq_time;
	s64 ocp_trigger_delay_us;

	ocp_irq_time = ktime_get();
	ocp_trigger_delay_us = ktime_us_delta(ocp_irq_time,
						vreg->vs_enable_time);

	/*
	 * Reset the OCP count if there is a large delay between switch enable
	 * and when OCP triggers.  This is indicative of a hotplug event as
	 * opposed to a fault.
	 */
	if (ocp_trigger_delay_us > SPMI_VS_OCP_FAULT_DELAY_US)
		vreg->ocp_count = 0;

	/* Wait for switch output to settle back to 0 V after OCP triggered. */
	udelay(SPMI_VS_OCP_FALL_DELAY_US);

	vreg->ocp_count++;

	if (vreg->ocp_count == 1) {
		/* Immediately clear the over current condition. */
		spmi_regulator_vs_clear_ocp(vreg);
	} else if (vreg->ocp_count <= vreg->ocp_max_retries) {
		/* Schedule the over current clear task to run later. */
		schedule_delayed_work(&vreg->ocp_work,
			msecs_to_jiffies(vreg->ocp_retry_delay_ms) + 1);
	} else {
		dev_err(vreg->dev,
			"OCP triggered %d times; no further retries\n",
			vreg->ocp_count);
	}

	return IRQ_HANDLED;
}