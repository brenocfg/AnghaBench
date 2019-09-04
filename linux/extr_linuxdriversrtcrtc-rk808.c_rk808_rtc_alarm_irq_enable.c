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
struct rk808_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rk808_rtc* dev_get_drvdata (struct device*) ; 
 int rk808_rtc_start_alarm (struct rk808_rtc*) ; 
 int rk808_rtc_stop_alarm (struct rk808_rtc*) ; 

__attribute__((used)) static int rk808_rtc_alarm_irq_enable(struct device *dev,
				      unsigned int enabled)
{
	struct rk808_rtc *rk808_rtc = dev_get_drvdata(dev);

	if (enabled)
		return rk808_rtc_start_alarm(rk808_rtc);

	return rk808_rtc_stop_alarm(rk808_rtc);
}