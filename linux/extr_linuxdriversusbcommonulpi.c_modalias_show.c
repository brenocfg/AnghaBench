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
struct TYPE_2__ {int vendor; int product; } ;
struct ulpi {TYPE_1__ id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int of_device_modalias (struct device*,char*,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int,int) ; 
 struct ulpi* to_ulpi_dev (struct device*) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	int len;
	struct ulpi *ulpi = to_ulpi_dev(dev);

	len = of_device_modalias(dev, buf, PAGE_SIZE);
	if (len != -ENODEV)
		return len;

	return sprintf(buf, "ulpi:v%04xp%04x\n",
		       ulpi->id.vendor, ulpi->id.product);
}