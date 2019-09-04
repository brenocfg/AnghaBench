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
struct s3c2410_wdt {scalar_t__ reg_base; TYPE_1__* drv_data; int /*<<< orphan*/  wdt_device; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int QUIRK_HAS_WTCLRINT_REG ; 
 scalar_t__ S3C2410_WTCLRINT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct s3c2410_wdt* platform_get_drvdata (void*) ; 
 int /*<<< orphan*/  s3c2410wdt_keepalive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t s3c2410wdt_irq(int irqno, void *param)
{
	struct s3c2410_wdt *wdt = platform_get_drvdata(param);

	dev_info(wdt->dev, "watchdog timer expired (irq)\n");

	s3c2410wdt_keepalive(&wdt->wdt_device);

	if (wdt->drv_data->quirks & QUIRK_HAS_WTCLRINT_REG)
		writel(0x1, wdt->reg_base + S3C2410_WTCLRINT);

	return IRQ_HANDLED;
}