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
struct tps65910_reg {int num_regulators; int /*<<< orphan*/ * rdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tps65910_reg* platform_get_drvdata (struct platform_device*) ; 
 int tps65910_set_ext_sleep_config (struct tps65910_reg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tps65910_shutdown(struct platform_device *pdev)
{
	struct tps65910_reg *pmic = platform_get_drvdata(pdev);
	int i;

	/*
	 * Before bootloader jumps to kernel, it makes sure that required
	 * external control signals are in desired state so that given rails
	 * can be configure accordingly.
	 * If rails are configured to be controlled from external control
	 * then before shutting down/rebooting the system, the external
	 * control configuration need to be remove from the rails so that
	 * its output will be available as per register programming even
	 * if external controls are removed. This is require when the POR
	 * value of the control signals are not in active state and before
	 * bootloader initializes it, the system requires the rail output
	 * to be active for booting.
	 */
	for (i = 0; i < pmic->num_regulators; i++) {
		int err;
		if (!pmic->rdev[i])
			continue;

		err = tps65910_set_ext_sleep_config(pmic, i, 0);
		if (err < 0)
			dev_err(&pdev->dev,
				"Error in clearing external control\n");
	}
}