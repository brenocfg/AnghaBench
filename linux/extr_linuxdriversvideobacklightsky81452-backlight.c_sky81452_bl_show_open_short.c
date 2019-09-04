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
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int SKY81452_REG4 ; 
 unsigned int SKY81452_REG5 ; 
 unsigned int SKY81452_SHRT ; 
 struct regmap* bl_get_data (int /*<<< orphan*/ ) ; 
 int regmap_read (struct regmap*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  to_backlight_device (struct device*) ; 

__attribute__((used)) static ssize_t sky81452_bl_show_open_short(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct regmap *regmap = bl_get_data(to_backlight_device(dev));
	unsigned int reg, value = 0;
	char tmp[3];
	int i, ret;

	reg = !strcmp(attr->attr.name, "open") ? SKY81452_REG5 : SKY81452_REG4;
	ret = regmap_read(regmap, reg, &value);
	if (ret < 0)
		return ret;

	if (value & SKY81452_SHRT) {
		*buf = 0;
		for (i = 0; i < 6; i++) {
			if (value & 0x01) {
				sprintf(tmp, "%d ", i + 1);
				strcat(buf, tmp);
			}
			value >>= 1;
		}
		strcat(buf, "\n");
	} else {
		strcpy(buf, "none\n");
	}

	return strlen(buf);
}