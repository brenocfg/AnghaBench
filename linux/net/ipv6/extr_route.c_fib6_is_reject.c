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
typedef  int u32 ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IPV6_ADDR_LOOPBACK ; 
 int RTF_LOCAL ; 
 int RTF_REJECT ; 

__attribute__((used)) static bool fib6_is_reject(u32 flags, struct net_device *dev, int addr_type)
{
	if ((flags & RTF_REJECT) ||
	    (dev && (dev->flags & IFF_LOOPBACK) &&
	     !(addr_type & IPV6_ADDR_LOOPBACK) &&
	     !(flags & RTF_LOCAL)))
		return true;

	return false;
}