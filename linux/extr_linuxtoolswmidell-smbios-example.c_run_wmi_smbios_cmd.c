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
struct dell_wmi_smbios_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELL_WMI_SMBIOS_CMD ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct dell_wmi_smbios_buffer*) ; 
 int /*<<< orphan*/  ioctl_devfs ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_wmi_smbios_cmd(struct dell_wmi_smbios_buffer *buffer)
{
	int fd;
	int ret;

	fd = open(ioctl_devfs, O_NONBLOCK);
	ret = ioctl(fd, DELL_WMI_SMBIOS_CMD, buffer);
	close(fd);
	return ret;
}