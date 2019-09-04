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
struct max17211_device_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ MAX1721X_REG_SER_HEX ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int get_sn_string(struct max17211_device_info *info, char *str)
{
	unsigned int val[3];

	if (!str)
		return -EFAULT;

	if (regmap_read(info->regmap, MAX1721X_REG_SER_HEX, &val[0]))
		return -EFAULT;
	if (regmap_read(info->regmap, MAX1721X_REG_SER_HEX + 1, &val[1]))
		return -EFAULT;
	if (regmap_read(info->regmap, MAX1721X_REG_SER_HEX + 2, &val[2]))
		return -EFAULT;

	snprintf(str, 13, "%04X%04X%04X", val[0], val[1], val[2]);
	return 0;
}