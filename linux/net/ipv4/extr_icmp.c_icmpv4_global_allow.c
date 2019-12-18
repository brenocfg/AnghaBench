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
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ icmp_global_allow () ; 
 scalar_t__ icmpv4_mask_allow (struct net*,int,int) ; 

__attribute__((used)) static bool icmpv4_global_allow(struct net *net, int type, int code)
{
	if (icmpv4_mask_allow(net, type, code))
		return true;

	if (icmp_global_allow())
		return true;

	return false;
}