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
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static bool get_autoflowlabel_enabled(void)
{
	int fd, ret;
	char val;

	fd = open("/proc/sys/net/ipv6/auto_flowlabels", O_RDONLY);
	if (fd == -1)
		error(1, errno, "open sysctl");

	ret = read(fd, &val, 1);
	if (ret == -1)
		error(1, errno, "read sysctl");
	if (ret == 0)
		error(1, 0, "read sysctl: 0");

	if (close(fd))
		error(1, errno, "close sysctl");

	return val == '1';
}