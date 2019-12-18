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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  if_indextoname (int,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 size_t read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_vendor_id(int ifindex)
{
	char ifname[IF_NAMESIZE], path[64], buf[8];
	ssize_t len;
	int fd;

	if (!if_indextoname(ifindex, ifname))
		return -1;

	snprintf(path, sizeof(path), "/sys/class/net/%s/device/vendor", ifname);

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return -1;

	len = read(fd, buf, sizeof(buf));
	close(fd);
	if (len < 0)
		return -1;
	if (len >= (ssize_t)sizeof(buf))
		return -1;
	buf[len] = '\0';

	return strtol(buf, NULL, 0);
}