#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeout; } ;
struct meson_wdt_dev {scalar_t__ wdt_base; TYPE_2__* data; TYPE_1__ wdt_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 scalar_t__ MESON_WDT_TC ; 
 int /*<<< orphan*/  meson_wdt_change_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_wdt_ping (struct watchdog_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct meson_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_wdt_start(struct watchdog_device *wdt_dev)
{
	struct meson_wdt_dev *meson_wdt = watchdog_get_drvdata(wdt_dev);
	u32 reg;

	meson_wdt_change_timeout(wdt_dev, meson_wdt->wdt_dev.timeout);
	meson_wdt_ping(wdt_dev);

	reg = readl(meson_wdt->wdt_base + MESON_WDT_TC);
	reg |= meson_wdt->data->enable;
	writel(reg, meson_wdt->wdt_base + MESON_WDT_TC);

	return 0;
}