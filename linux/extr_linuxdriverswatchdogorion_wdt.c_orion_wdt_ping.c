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
struct watchdog_device {int timeout; } ;
struct orion_watchdog {int clk_rate; TYPE_1__* data; scalar_t__ reg; } ;
struct TYPE_2__ {scalar_t__ wdt_counter_offset; } ;

/* Variables and functions */
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int orion_wdt_ping(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);
	/* Reload watchdog duration */
	writel(dev->clk_rate * wdt_dev->timeout,
	       dev->reg + dev->data->wdt_counter_offset);
	return 0;
}