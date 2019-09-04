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
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ ** scale_avail ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t in_voltage_scale_available_show(struct device *dev,
					       struct device_attribute *attr,
					       char *buf)
{
	int i, len = 0;

	for (i = 0; i < ARRAY_SIZE(scale_avail); i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d.%06u ",
				 scale_avail[i][0], scale_avail[i][1]);

	buf[len - 1] = '\n';

	return len;
}