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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  hard_header_len; } ;
struct dn_ifaddr {int /*<<< orphan*/  ifa_local; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DN_RT_PKT_HELO ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* dn_alloc_skb (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_dn2eth (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_rt_all_rt_mcast ; 
 int /*<<< orphan*/  dn_rt_finish_output (struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void dn_send_ptp_hello(struct net_device *dev, struct dn_ifaddr *ifa)
{
	int tdlen = 16;
	int size = dev->hard_header_len + 2 + 4 + tdlen;
	struct sk_buff *skb = dn_alloc_skb(NULL, size, GFP_ATOMIC);
	int i;
	unsigned char *ptr;
	char src[ETH_ALEN];

	if (skb == NULL)
		return ;

	skb->dev = dev;
	skb_push(skb, dev->hard_header_len);
	ptr = skb_put(skb, 2 + 4 + tdlen);

	*ptr++ = DN_RT_PKT_HELO;
	*((__le16 *)ptr) = ifa->ifa_local;
	ptr += 2;
	*ptr++ = tdlen;

	for(i = 0; i < tdlen; i++)
		*ptr++ = 0252;

	dn_dn2eth(src, ifa->ifa_local);
	dn_rt_finish_output(skb, dn_rt_all_rt_mcast, src);
}