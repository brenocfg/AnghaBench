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
struct spm_driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_SLEEP_MODE_SPC ; 
 int /*<<< orphan*/  PM_SLEEP_MODE_STBY ; 
 struct spm_driver_data* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_spm_drv ; 
 int cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_pm_collapse ; 
 int /*<<< orphan*/  spm_set_low_power_mode (struct spm_driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_cpu_spc(void)
{
	int ret;
	struct spm_driver_data *drv = __this_cpu_read(cpu_spm_drv);

	spm_set_low_power_mode(drv, PM_SLEEP_MODE_SPC);
	ret = cpu_suspend(0, qcom_pm_collapse);
	/*
	 * ARM common code executes WFI without calling into our driver and
	 * if the SPM mode is not reset, then we may accidently power down the
	 * cpu when we intended only to gate the cpu clock.
	 * Ensure the state is set to standby before returning.
	 */
	spm_set_low_power_mode(drv, PM_SLEEP_MODE_STBY);

	return ret;
}