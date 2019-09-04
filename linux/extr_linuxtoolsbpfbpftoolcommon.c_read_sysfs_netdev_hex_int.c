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
typedef  int /*<<< orphan*/  full_path ;

/* Variables and functions */
 int read_sysfs_hex_int (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static int read_sysfs_netdev_hex_int(char *devname, const char *entry_name)
{
	char full_path[64];

	snprintf(full_path, sizeof(full_path), "/sys/class/net/%s/device/%s",
		 devname, entry_name);

	return read_sysfs_hex_int(full_path);
}