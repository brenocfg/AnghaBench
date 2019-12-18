#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* sa_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa_family; } ;
struct ifreq {TYPE_1__ ifr_hwaddr; int /*<<< orphan*/  ifr_name; TYPE_2__ ifr_addr; } ;
typedef  scalar_t__ __u8 ;
typedef  int __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCGIFHWADDR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static __be64 getmac(char *iface)
{
	struct ifreq ifr;
	__be64 mac = 0;
	int fd, i;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);
	if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
		printf("ioctl failed leaving....\n");
		return -1;
	}
	for (i = 0; i < 6 ; i++)
		*((__u8 *)&mac + i) = (__u8)ifr.ifr_hwaddr.sa_data[i];
	close(fd);
	return mac;
}