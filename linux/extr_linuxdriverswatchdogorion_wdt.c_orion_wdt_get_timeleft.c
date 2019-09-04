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
struct watchdog_device {int dummy; } ;
struct orion_watchdog {unsigned int clk_rate; TYPE_1__* data; scalar_t__ reg; } ;
struct TYPE_2__ {scalar_t__ wdt_counter_offset; } ;

/* Variables and functions */
 unsigned int readl (scalar_t__) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int orion_wdt_get_timeleft(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);
	return readl(dev->reg + dev->data->wdt_counter_offset) / dev->clk_rate;
}