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
struct ifaddrmsg {int dummy; } ;
struct ifa_cacheinfo {int dummy; } ;

/* Variables and functions */
 int NLMSG_ALIGN (int) ; 
 int nla_total_size (int) ; 

__attribute__((used)) static inline int inet6_ifaddr_msgsize(void)
{
	return NLMSG_ALIGN(sizeof(struct ifaddrmsg))
	       + nla_total_size(16) /* IFA_LOCAL */
	       + nla_total_size(16) /* IFA_ADDRESS */
	       + nla_total_size(sizeof(struct ifa_cacheinfo))
	       + nla_total_size(4)  /* IFA_FLAGS */
	       + nla_total_size(4)  /* IFA_RT_PRIORITY */;
}