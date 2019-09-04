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
struct sk_buff {int dummy; } ;
struct pimhdr {int dummy; } ;
struct net_bridge_port {int dummy; } ;
struct net_bridge {int dummy; } ;
typedef  int /*<<< orphan*/  _pimhdr ;

/* Variables and functions */
 scalar_t__ PIM_TYPE_HELLO ; 
 scalar_t__ PIM_VERSION ; 
 int /*<<< orphan*/  br_multicast_mark_router (struct net_bridge*,struct net_bridge_port*) ; 
 scalar_t__ pim_hdr_type (struct pimhdr*) ; 
 scalar_t__ pim_hdr_version (struct pimhdr*) ; 
 struct pimhdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct pimhdr*) ; 
 unsigned int skb_transport_offset (struct sk_buff const*) ; 

__attribute__((used)) static void br_multicast_pim(struct net_bridge *br,
			     struct net_bridge_port *port,
			     const struct sk_buff *skb)
{
	unsigned int offset = skb_transport_offset(skb);
	struct pimhdr *pimhdr, _pimhdr;

	pimhdr = skb_header_pointer(skb, offset, sizeof(_pimhdr), &_pimhdr);
	if (!pimhdr || pim_hdr_version(pimhdr) != PIM_VERSION ||
	    pim_hdr_type(pimhdr) != PIM_TYPE_HELLO)
		return;

	br_multicast_mark_router(br, port);
}