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
struct TYPE_2__ {int /*<<< orphan*/  er_SerialNumber; } ;
struct zorro_dev {TYPE_1__ rom; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct zorro_dev* to_zorro_dev (struct device*) ; 

__attribute__((used)) static ssize_t serial_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct zorro_dev *z;

	z = to_zorro_dev(dev);
	return sprintf(buf, "0x%08x\n", be32_to_cpu(z->rom.er_SerialNumber));
}