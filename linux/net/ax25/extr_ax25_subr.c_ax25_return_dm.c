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
struct net_device {int /*<<< orphan*/  hard_header_len; } ;
typedef  int /*<<< orphan*/  ax25_digi ;
typedef  int /*<<< orphan*/  ax25_address ;

/* Variables and functions */
 char AX25_DM ; 
 int /*<<< orphan*/  AX25_MODULUS ; 
 char AX25_PF ; 
 int /*<<< orphan*/  AX25_RESPONSE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_addr_build (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_addr_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax25_digi_invert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax25_queue_xmit (struct sk_buff*,struct net_device*) ; 
 char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

void ax25_return_dm(struct net_device *dev, ax25_address *src, ax25_address *dest, ax25_digi *digi)
{
	struct sk_buff *skb;
	char *dptr;
	ax25_digi retdigi;

	if (dev == NULL)
		return;

	if ((skb = alloc_skb(dev->hard_header_len + 1, GFP_ATOMIC)) == NULL)
		return;	/* Next SABM will get DM'd */

	skb_reserve(skb, dev->hard_header_len);
	skb_reset_network_header(skb);

	ax25_digi_invert(digi, &retdigi);

	dptr = skb_put(skb, 1);

	*dptr = AX25_DM | AX25_PF;

	/*
	 *	Do the address ourselves
	 */
	dptr  = skb_push(skb, ax25_addr_size(digi));
	dptr += ax25_addr_build(dptr, dest, src, &retdigi, AX25_RESPONSE, AX25_MODULUS);

	ax25_queue_xmit(skb, dev);
}