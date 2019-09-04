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
struct sk_buff {int dummy; } ;
struct net_device {void* dev_addr; } ;

/* Variables and functions */
 unsigned short ETH_P_PHONET ; 
 int /*<<< orphan*/ * skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int pn_header_create(struct sk_buff *skb, struct net_device *dev,
				unsigned short type, const void *daddr,
				const void *saddr, unsigned int len)
{
	u8 *media = skb_push(skb, 1);

	if (type != ETH_P_PHONET)
		return -1;

	if (!saddr)
		saddr = dev->dev_addr;
	*media = *(const u8 *)saddr;
	return 1;
}