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
struct net_device {int addr_len; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  ETH_ALEN 129 
#define  EUI64_ADDR_LEN 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  lowpan_iphc_uncompress_eui48_lladdr (struct in6_addr*,void const*) ; 
 int /*<<< orphan*/  lowpan_iphc_uncompress_eui64_lladdr (struct in6_addr*,void const*) ; 

__attribute__((used)) static void lowpan_iphc_uncompress_lladdr(const struct net_device *dev,
					  struct in6_addr *ipaddr,
					  const void *lladdr)
{
	switch (dev->addr_len) {
	case ETH_ALEN:
		lowpan_iphc_uncompress_eui48_lladdr(ipaddr, lladdr);
		break;
	case EUI64_ADDR_LEN:
		lowpan_iphc_uncompress_eui64_lladdr(ipaddr, lladdr);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}
}