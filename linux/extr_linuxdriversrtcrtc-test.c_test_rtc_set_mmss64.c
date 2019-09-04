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
typedef  scalar_t__ time64_t ;
struct rtc_test_data {scalar_t__ offset; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rtc_test_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ ktime_get_real_seconds () ; 

__attribute__((used)) static int test_rtc_set_mmss64(struct device *dev, time64_t secs)
{
	struct rtc_test_data *rtd = dev_get_drvdata(dev);

	rtd->offset = secs - ktime_get_real_seconds();

	return 0;
}