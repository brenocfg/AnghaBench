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
struct rio_dev {int pef; TYPE_1__* rswitch; int /*<<< orphan*/  swpinfo; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__* nextdev; } ;

/* Variables and functions */
 int RIO_GET_TOTAL_PORTS (int /*<<< orphan*/ ) ; 
 int RIO_PEF_SWITCH ; 
 char* rio_name (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct rio_dev* to_rio_dev (struct device*) ; 

__attribute__((used)) static ssize_t lnext_show(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct rio_dev *rdev = to_rio_dev(dev);
	char *str = buf;
	int i;

	if (rdev->pef & RIO_PEF_SWITCH) {
		for (i = 0; i < RIO_GET_TOTAL_PORTS(rdev->swpinfo); i++) {
			if (rdev->rswitch->nextdev[i])
				str += sprintf(str, "%s\n",
					rio_name(rdev->rswitch->nextdev[i]));
			else
				str += sprintf(str, "null\n");
		}
	}

	return str - buf;
}