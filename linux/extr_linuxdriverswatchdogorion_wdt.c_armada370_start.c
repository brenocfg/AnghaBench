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
typedef  int u32 ;
struct watchdog_device {int timeout; } ;
struct orion_watchdog {int clk_rate; scalar_t__ rstout; TYPE_1__* data; scalar_t__ reg; } ;
struct TYPE_2__ {int rstout_enable_bit; int /*<<< orphan*/  wdt_enable_bit; scalar_t__ wdt_counter_offset; } ;

/* Variables and functions */
 scalar_t__ TIMER_A370_STATUS ; 
 scalar_t__ TIMER_CTRL ; 
 int /*<<< orphan*/  WDT_A370_EXPIRED ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int armada370_start(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);
	u32 reg;

	/* Set watchdog duration */
	writel(dev->clk_rate * wdt_dev->timeout,
	       dev->reg + dev->data->wdt_counter_offset);

	/* Clear the watchdog expiration bit */
	atomic_io_modify(dev->reg + TIMER_A370_STATUS, WDT_A370_EXPIRED, 0);

	/* Enable watchdog timer */
	atomic_io_modify(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit,
						dev->data->wdt_enable_bit);

	/* Enable reset on watchdog */
	reg = readl(dev->rstout);
	reg |= dev->data->rstout_enable_bit;
	writel(reg, dev->rstout);
	return 0;
}