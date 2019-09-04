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
 int /*<<< orphan*/  QCOM_SCM_CPU_PWR_DOWN_L2_ON ; 
 int /*<<< orphan*/  qcom_scm_cpu_power_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_pm_collapse(unsigned long int unused)
{
	qcom_scm_cpu_power_down(QCOM_SCM_CPU_PWR_DOWN_L2_ON);

	/*
	 * Returns here only if there was a pending interrupt and we did not
	 * power down as a result.
	 */
	return -1;
}