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
struct dc_rtc {int dummy; } ;

/* Variables and functions */
 int dc_rtc_write (struct dc_rtc*,unsigned long) ; 
 struct dc_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int dc_rtc_set_mmss(struct device *dev, unsigned long secs)
{
	struct dc_rtc *rtc = dev_get_drvdata(dev);

	return dc_rtc_write(rtc, secs);
}