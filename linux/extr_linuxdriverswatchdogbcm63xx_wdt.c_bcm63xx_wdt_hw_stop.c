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
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WDT_CTL_REG ; 
 int /*<<< orphan*/  WDT_STOP_1 ; 
 int /*<<< orphan*/  WDT_STOP_2 ; 
 TYPE_1__ bcm63xx_wdt_device ; 
 int /*<<< orphan*/  bcm_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bcm63xx_wdt_hw_stop(void)
{
	bcm_writel(WDT_STOP_1, bcm63xx_wdt_device.regs + WDT_CTL_REG);
	bcm_writel(WDT_STOP_2, bcm63xx_wdt_device.regs + WDT_CTL_REG);
}