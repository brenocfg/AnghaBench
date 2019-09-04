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
struct ifreq {unsigned int ifr_mtu; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFMTU ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static unsigned int get_device_mtu(int fd, const char *ifname)
{
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(ifr));

	strcpy(ifr.ifr_name, ifname);

	if (ioctl(fd, SIOCGIFMTU, &ifr))
		error(1, errno, "ioctl get mtu");

	return ifr.ifr_mtu;
}