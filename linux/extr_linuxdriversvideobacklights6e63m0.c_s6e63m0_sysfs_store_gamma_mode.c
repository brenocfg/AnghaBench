#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s6e63m0 {int gamma_mode; struct backlight_device* bd; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/ * gamma_22_table; int /*<<< orphan*/ * gamma_17_table; int /*<<< orphan*/ * gamma_19_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  _s6e63m0_gamma_ctl (struct s6e63m0*,int /*<<< orphan*/ ) ; 
 struct s6e63m0* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 TYPE_2__ gamma_table ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t s6e63m0_sysfs_store_gamma_mode(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t len)
{
	struct s6e63m0 *lcd = dev_get_drvdata(dev);
	struct backlight_device *bd = NULL;
	int brightness, rc;

	rc = kstrtouint(buf, 0, &lcd->gamma_mode);
	if (rc < 0)
		return rc;

	bd = lcd->bd;

	brightness = bd->props.brightness;

	switch (lcd->gamma_mode) {
	case 0:
		_s6e63m0_gamma_ctl(lcd, gamma_table.gamma_22_table[brightness]);
		break;
	case 1:
		_s6e63m0_gamma_ctl(lcd, gamma_table.gamma_19_table[brightness]);
		break;
	case 2:
		_s6e63m0_gamma_ctl(lcd, gamma_table.gamma_17_table[brightness]);
		break;
	default:
		dev_info(dev, "gamma mode could be 0:2.2, 1:1.9 or 2:1.7\n");
		_s6e63m0_gamma_ctl(lcd, gamma_table.gamma_22_table[brightness]);
		break;
	}
	return len;
}