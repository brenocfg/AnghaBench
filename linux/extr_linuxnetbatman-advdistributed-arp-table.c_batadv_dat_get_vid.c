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

/* Variables and functions */
 unsigned short BATADV_VLAN_HAS_TAG ; 
 scalar_t__ VLAN_HLEN ; 
 unsigned short batadv_get_vid (struct sk_buff*,int) ; 

__attribute__((used)) static unsigned short batadv_dat_get_vid(struct sk_buff *skb, int *hdr_size)
{
	unsigned short vid;

	vid = batadv_get_vid(skb, *hdr_size);

	/* ARP parsing functions jump forward of hdr_size + ETH_HLEN.
	 * If the header contained in the packet is a VLAN one (which is longer)
	 * hdr_size is updated so that the functions will still skip the
	 * correct amount of bytes.
	 */
	if (vid & BATADV_VLAN_HAS_TAG)
		*hdr_size += VLAN_HLEN;

	return vid;
}