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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  mrst_poweroff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_mrst_do_shutdown () ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void vrtc_mrst_platform_shutdown(struct platform_device *pdev)
{
	if (system_state == SYSTEM_POWER_OFF && !mrst_poweroff(&pdev->dev))
		return;

	rtc_mrst_do_shutdown();
}