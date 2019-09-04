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
struct sk_buff {scalar_t__ data; } ;
struct arphdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 

__attribute__((used)) static u8 *batadv_arp_hw_src(struct sk_buff *skb, int hdr_size)
{
	u8 *addr;

	addr = (u8 *)(skb->data + hdr_size);
	addr += ETH_HLEN + sizeof(struct arphdr);

	return addr;
}