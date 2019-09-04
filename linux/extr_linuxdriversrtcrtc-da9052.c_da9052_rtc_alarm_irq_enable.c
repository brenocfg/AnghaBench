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
struct device {int dummy; } ;
struct da9052_rtc {int dummy; } ;

/* Variables and functions */
 int da9052_rtc_enable_alarm (struct da9052_rtc*,unsigned int) ; 
 struct da9052_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int da9052_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct da9052_rtc *rtc = dev_get_drvdata(dev);

	return da9052_rtc_enable_alarm(rtc, enabled);
}