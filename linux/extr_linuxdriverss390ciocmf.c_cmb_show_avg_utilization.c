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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  avg_utilization ; 
 unsigned long cmf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t cmb_show_avg_utilization(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	unsigned long u = cmf_read(to_ccwdev(dev), avg_utilization);

	return sprintf(buf, "%02lu.%01lu%%\n", u / 10, u % 10);
}