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
typedef  int u8 ;
struct w1_slave {int* family_data; TYPE_1__* family; } ;
struct therm_info {int* rom; int crc; scalar_t__ verdict; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int fid; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 struct w1_slave* dev_to_w1_slave (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int read_therm (struct device*,struct w1_slave*,struct therm_info*) ; 
 int snprintf (char*,int,char*,int,...) ; 
 int w1_convert_temp (int*,int) ; 

__attribute__((used)) static ssize_t w1_slave_show(struct device *device,
			     struct device_attribute *attr, char *buf)
{
	struct w1_slave *sl = dev_to_w1_slave(device);
	struct therm_info info;
	u8 *family_data = sl->family_data;
	int ret, i;
	ssize_t c = PAGE_SIZE;
	u8 fid = sl->family->fid;

	ret = read_therm(device, sl, &info);
	if (ret)
		return ret;

	for (i = 0; i < 9; ++i)
		c -= snprintf(buf + PAGE_SIZE - c, c, "%02x ", info.rom[i]);
	c -= snprintf(buf + PAGE_SIZE - c, c, ": crc=%02x %s\n",
		      info.crc, (info.verdict) ? "YES" : "NO");
	if (info.verdict)
		memcpy(family_data, info.rom, sizeof(info.rom));
	else
		dev_warn(device, "Read failed CRC check\n");

	for (i = 0; i < 9; ++i)
		c -= snprintf(buf + PAGE_SIZE - c, c, "%02x ",
			      ((u8 *)family_data)[i]);

	c -= snprintf(buf + PAGE_SIZE - c, c, "t=%d\n",
			w1_convert_temp(info.rom, fid));
	ret = PAGE_SIZE - c;
	return ret;
}