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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_F_TENTATIVE ; 
 int ipv6_chk_addr_and_flags (struct net*,struct in6_addr const*,struct net_device const*,int,int,int /*<<< orphan*/ ) ; 

int ipv6_chk_addr(struct net *net, const struct in6_addr *addr,
		  const struct net_device *dev, int strict)
{
	return ipv6_chk_addr_and_flags(net, addr, dev, !dev,
				       strict, IFA_F_TENTATIVE);
}