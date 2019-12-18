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
struct TYPE_2__ {scalar_t__ sa_family; } ;
struct ifreq {TYPE_1__ ifr_hwaddr; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE80211_RADIOTAP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCGIFHWADDR ; 
 int /*<<< orphan*/  capture_sock ; 
 int /*<<< orphan*/  ifname ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int check_type(void)
{
	struct ifreq ifr;

	strncpy(ifr.ifr_name, ifname, IFNAMSIZ);

	if (ioctl(capture_sock, SIOCGIFHWADDR, &ifr) < 0)
		return -1;

	return (ifr.ifr_hwaddr.sa_family == ARPHRD_IEEE80211_RADIOTAP);
}