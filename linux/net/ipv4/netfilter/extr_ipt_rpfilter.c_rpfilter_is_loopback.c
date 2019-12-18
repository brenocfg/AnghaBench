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
struct sk_buff {scalar_t__ pkt_type; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 scalar_t__ PACKET_LOOPBACK ; 

__attribute__((used)) static bool
rpfilter_is_loopback(const struct sk_buff *skb, const struct net_device *in)
{
	return skb->pkt_type == PACKET_LOOPBACK || in->flags & IFF_LOOPBACK;
}