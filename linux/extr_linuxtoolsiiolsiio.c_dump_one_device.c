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

/* Variables and functions */
 int EINVAL ; 
 int IIO_MAX_NAME_LENGTH ; 
 scalar_t__ VERBLEVEL_SENSORS ; 
 int dump_channels (char const*) ; 
 int /*<<< orphan*/  iio_dir ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int read_sysfs_string (char*,char const*,char*) ; 
 int sscanf (char const*,char*,int*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_device ; 
 scalar_t__ verblevel ; 

__attribute__((used)) static int dump_one_device(const char *dev_dir_name)
{
	char name[IIO_MAX_NAME_LENGTH];
	int dev_idx;
	int ret;

	ret = sscanf(dev_dir_name + strlen(iio_dir) + strlen(type_device), "%i",
		     &dev_idx);
	if (ret != 1)
		return -EINVAL;

	ret = read_sysfs_string("name", dev_dir_name, name);
	if (ret < 0)
		return ret;

	printf("Device %03d: %s\n", dev_idx, name);

	if (verblevel >= VERBLEVEL_SENSORS)
		return dump_channels(dev_dir_name);

	return 0;
}