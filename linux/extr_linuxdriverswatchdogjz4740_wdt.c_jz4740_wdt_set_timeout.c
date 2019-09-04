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
typedef  unsigned short u16 ;
struct watchdog_device {unsigned int timeout; } ;
struct jz4740_wdt_drvdata {scalar_t__ base; int /*<<< orphan*/  rtc_clk; } ;

/* Variables and functions */
 scalar_t__ JZ_REG_WDT_COUNTER_ENABLE ; 
 scalar_t__ JZ_REG_WDT_TIMER_CONTROL ; 
 scalar_t__ JZ_REG_WDT_TIMER_COUNTER ; 
 scalar_t__ JZ_REG_WDT_TIMER_DATA ; 
 unsigned short JZ_WDT_CLOCK_DIV_1 ; 
 unsigned short JZ_WDT_CLOCK_DIV_1024 ; 
 int JZ_WDT_CLOCK_DIV_SHIFT ; 
 unsigned short JZ_WDT_CLOCK_RTC ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct jz4740_wdt_drvdata* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static int jz4740_wdt_set_timeout(struct watchdog_device *wdt_dev,
				    unsigned int new_timeout)
{
	struct jz4740_wdt_drvdata *drvdata = watchdog_get_drvdata(wdt_dev);
	unsigned int rtc_clk_rate;
	unsigned int timeout_value;
	unsigned short clock_div = JZ_WDT_CLOCK_DIV_1;

	rtc_clk_rate = clk_get_rate(drvdata->rtc_clk);

	timeout_value = rtc_clk_rate * new_timeout;
	while (timeout_value > 0xffff) {
		if (clock_div == JZ_WDT_CLOCK_DIV_1024) {
			/* Requested timeout too high;
			* use highest possible value. */
			timeout_value = 0xffff;
			break;
		}
		timeout_value >>= 2;
		clock_div += (1 << JZ_WDT_CLOCK_DIV_SHIFT);
	}

	writeb(0x0, drvdata->base + JZ_REG_WDT_COUNTER_ENABLE);
	writew(clock_div, drvdata->base + JZ_REG_WDT_TIMER_CONTROL);

	writew((u16)timeout_value, drvdata->base + JZ_REG_WDT_TIMER_DATA);
	writew(0x0, drvdata->base + JZ_REG_WDT_TIMER_COUNTER);
	writew(clock_div | JZ_WDT_CLOCK_RTC,
		drvdata->base + JZ_REG_WDT_TIMER_CONTROL);

	writeb(0x1, drvdata->base + JZ_REG_WDT_COUNTER_ENABLE);

	wdt_dev->timeout = new_timeout;
	return 0;
}