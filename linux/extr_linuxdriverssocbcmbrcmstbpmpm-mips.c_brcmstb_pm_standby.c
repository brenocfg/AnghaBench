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
 int /*<<< orphan*/  CAUSEF_IV ; 
 int /*<<< orphan*/  ST0_BEV ; 
 int /*<<< orphan*/  brcmstb_pm_handshake () ; 
 int /*<<< orphan*/  brcmstb_pm_s2 () ; 
 int /*<<< orphan*/  brcmstb_pm_s3 () ; 
 int /*<<< orphan*/  clear_c0_cause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_disable_hazard () ; 
 int /*<<< orphan*/  set_c0_cause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_c0_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmstb_pm_standby(bool deep_standby)
{
	brcmstb_pm_handshake();

	/* Send IRQs to BMIPS_WARM_RESTART_VEC */
	clear_c0_cause(CAUSEF_IV);
	irq_disable_hazard();
	set_c0_status(ST0_BEV);
	irq_disable_hazard();

	if (deep_standby)
		brcmstb_pm_s3();
	else
		brcmstb_pm_s2();

	/* Send IRQs to normal runtime vectors */
	clear_c0_status(ST0_BEV);
	irq_disable_hazard();
	set_c0_cause(CAUSEF_IV);
	irq_disable_hazard();

	return 0;
}