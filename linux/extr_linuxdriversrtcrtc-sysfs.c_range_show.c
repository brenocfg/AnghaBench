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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_rtc_device (struct device*) ; 

__attribute__((used)) static ssize_t
range_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "[%lld,%llu]\n", to_rtc_device(dev)->range_min,
		       to_rtc_device(dev)->range_max);
}