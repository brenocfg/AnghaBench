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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  am33xx_pm_free_sram () ; 
 int /*<<< orphan*/  m3_ipc ; 
 int /*<<< orphan*/  suspend_set_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wkup_m3_ipc_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_pm_remove(struct platform_device *pdev)
{
	suspend_set_ops(NULL);
	wkup_m3_ipc_put(m3_ipc);
	am33xx_pm_free_sram();
	return 0;
}