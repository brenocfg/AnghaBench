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
struct in6_addr {int dummy; } ;
struct ifla_cacheinfo {int dummy; } ;

/* Variables and functions */
 int DEVCONF_MAX ; 
 int ICMP6_MIB_MAX ; 
 int IPSTATS_MIB_MAX ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static inline size_t inet6_ifla6_size(void)
{
	return nla_total_size(4) /* IFLA_INET6_FLAGS */
	     + nla_total_size(sizeof(struct ifla_cacheinfo))
	     + nla_total_size(DEVCONF_MAX * 4) /* IFLA_INET6_CONF */
	     + nla_total_size(IPSTATS_MIB_MAX * 8) /* IFLA_INET6_STATS */
	     + nla_total_size(ICMP6_MIB_MAX * 8) /* IFLA_INET6_ICMP6STATS */
	     + nla_total_size(sizeof(struct in6_addr)) /* IFLA_INET6_TOKEN */
	     + nla_total_size(1) /* IFLA_INET6_ADDR_GEN_MODE */
	     + 0;
}