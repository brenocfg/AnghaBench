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
struct s6e63m0 {int gamma_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct s6e63m0* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t s6e63m0_sysfs_show_gamma_mode(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct s6e63m0 *lcd = dev_get_drvdata(dev);
	char temp[10];

	switch (lcd->gamma_mode) {
	case 0:
		sprintf(temp, "2.2 mode\n");
		strcat(buf, temp);
		break;
	case 1:
		sprintf(temp, "1.9 mode\n");
		strcat(buf, temp);
		break;
	case 2:
		sprintf(temp, "1.7 mode\n");
		strcat(buf, temp);
		break;
	default:
		dev_info(dev, "gamma mode could be 0:2.2, 1:1.9 or 2:1.7)n");
		break;
	}

	return strlen(buf);
}