#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct netif_saddr_data {int dummy; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct TYPE_3__ {unsigned int sa_family; } ;

/* Variables and functions */
 unsigned int AF_INET ; 
 unsigned int AF_INET6 ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int /*<<< orphan*/  gai_strerror (unsigned int) ; 
 int getifaddrs (struct ifaddrs**) ; 
 unsigned int getnameinfo (TYPE_1__*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_loopback (struct ifaddrs*) ; 
 int /*<<< orphan*/  netif_push (TYPE_1__*,struct netif_saddr_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static inline void netif_get_addrs_nix(struct netif_saddr_data *ifaddrs)
{
	struct ifaddrs *ifaddr, *ifa;
	unsigned int family, s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		warn("getifaddrs() failed");
		return;
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL || is_loopback(ifa))
			continue;

		family = ifa->ifa_addr->sa_family;

		if ((family == AF_INET) || (family == AF_INET6)) {
			s = getnameinfo(ifa->ifa_addr,
					(family == AF_INET)
						? sizeof(struct sockaddr_in)
						: sizeof(struct sockaddr_in6),
					host, NI_MAXHOST, NULL, 0,
					NI_NUMERICHOST);
			if (s != 0) {
				warn("getnameinfo() failed: %s",
				     gai_strerror(s));
				continue;
			}

			netif_push(ifa->ifa_addr, ifaddrs, ifa->ifa_name);
		}
	}

	freeifaddrs(ifaddr);
}