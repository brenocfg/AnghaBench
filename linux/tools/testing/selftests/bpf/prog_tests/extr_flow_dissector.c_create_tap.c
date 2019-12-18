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
struct ifreq {int ifr_flags; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int IFF_NAPI ; 
 int IFF_NAPI_FRAGS ; 
 int IFF_NO_PI ; 
 int IFF_TAP ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  TUNSETIFF ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int create_tap(const char *ifname)
{
	struct ifreq ifr = {
		.ifr_flags = IFF_TAP | IFF_NO_PI | IFF_NAPI | IFF_NAPI_FRAGS,
	};
	int fd, ret;

	strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));

	fd = open("/dev/net/tun", O_RDWR);
	if (fd < 0)
		return -1;

	ret = ioctl(fd, TUNSETIFF, &ifr);
	if (ret)
		return -1;

	return fd;
}