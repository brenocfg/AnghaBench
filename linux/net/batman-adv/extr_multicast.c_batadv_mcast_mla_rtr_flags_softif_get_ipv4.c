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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_MCAST_WANT_NO_RTR4 ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 scalar_t__ IN_DEV_MFORWARD (struct in_device*) ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 

__attribute__((used)) static u8 batadv_mcast_mla_rtr_flags_softif_get_ipv4(struct net_device *dev)
{
	struct in_device *in_dev = __in_dev_get_rcu(dev);

	if (in_dev && IN_DEV_MFORWARD(in_dev))
		return BATADV_NO_FLAGS;
	else
		return BATADV_MCAST_WANT_NO_RTR4;
}