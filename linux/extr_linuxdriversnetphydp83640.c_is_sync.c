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
typedef  int u8 ;
struct sk_buff {int* data; unsigned int len; } ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 unsigned int IP6_HLEN ; 
 unsigned int IPV4_HLEN (int*) ; 
 scalar_t__ OFF_PTP_CONTROL ; 
#define  PTP_CLASS_IPV4 130 
#define  PTP_CLASS_IPV6 129 
#define  PTP_CLASS_L2 128 
 int PTP_CLASS_PMASK ; 
 int PTP_CLASS_V1 ; 
 int PTP_CLASS_VLAN ; 
 unsigned int UDP_HLEN ; 
 scalar_t__ VLAN_HLEN ; 

__attribute__((used)) static int is_sync(struct sk_buff *skb, int type)
{
	u8 *data = skb->data, *msgtype;
	unsigned int offset = 0;

	if (type & PTP_CLASS_VLAN)
		offset += VLAN_HLEN;

	switch (type & PTP_CLASS_PMASK) {
	case PTP_CLASS_IPV4:
		offset += ETH_HLEN + IPV4_HLEN(data + offset) + UDP_HLEN;
		break;
	case PTP_CLASS_IPV6:
		offset += ETH_HLEN + IP6_HLEN + UDP_HLEN;
		break;
	case PTP_CLASS_L2:
		offset += ETH_HLEN;
		break;
	default:
		return 0;
	}

	if (type & PTP_CLASS_V1)
		offset += OFF_PTP_CONTROL;

	if (skb->len < offset + 1)
		return 0;

	msgtype = data + offset;

	return (*msgtype & 0xf) == 0;
}