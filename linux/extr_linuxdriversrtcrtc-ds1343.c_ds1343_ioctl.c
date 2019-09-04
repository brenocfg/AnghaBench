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

/* Variables and functions */
 int ENOIOCTLCMD ; 

__attribute__((used)) static int ds1343_ioctl(struct device *dev, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
#ifdef RTC_SET_CHARGE
	case RTC_SET_CHARGE:
	{
		int val;

		if (copy_from_user(&val, (int __user *)arg, sizeof(int)))
			return -EFAULT;

		return regmap_write(priv->map, DS1343_TRICKLE_REG, val);
	}
	break;
#endif
	}

	return -ENOIOCTLCMD;
}