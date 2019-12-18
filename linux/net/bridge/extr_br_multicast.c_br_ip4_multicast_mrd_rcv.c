#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_bridge_port {int dummy; } ;
struct net_bridge {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int ENOMSG ; 
 scalar_t__ IGMP_MRDISC_ADV ; 
 scalar_t__ IPPROTO_IGMP ; 
 int /*<<< orphan*/  br_multicast_mark_router (struct net_bridge*,struct net_bridge_port*) ; 
 TYPE_2__* igmp_hdr (struct sk_buff*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static int br_ip4_multicast_mrd_rcv(struct net_bridge *br,
				    struct net_bridge_port *port,
				    struct sk_buff *skb)
{
	if (ip_hdr(skb)->protocol != IPPROTO_IGMP ||
	    igmp_hdr(skb)->type != IGMP_MRDISC_ADV)
		return -ENOMSG;

	br_multicast_mark_router(br, port);

	return 0;
}