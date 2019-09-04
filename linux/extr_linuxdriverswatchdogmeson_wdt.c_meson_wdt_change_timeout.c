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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int dummy; } ;
struct meson_wdt_dev {scalar_t__ wdt_base; TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  count_unit; int /*<<< orphan*/  terminal_count_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_SEC_TO_TC (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ MESON_WDT_TC ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct meson_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_wdt_change_timeout(struct watchdog_device *wdt_dev,
				     unsigned int timeout)
{
	struct meson_wdt_dev *meson_wdt = watchdog_get_drvdata(wdt_dev);
	u32 reg;

	reg = readl(meson_wdt->wdt_base + MESON_WDT_TC);
	reg &= ~meson_wdt->data->terminal_count_mask;
	reg |= MESON_SEC_TO_TC(timeout, meson_wdt->data->count_unit);
	writel(reg, meson_wdt->wdt_base + MESON_WDT_TC);
}