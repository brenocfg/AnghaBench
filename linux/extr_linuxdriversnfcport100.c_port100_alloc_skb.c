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
struct port100 {scalar_t__ skb_headroom; scalar_t__ skb_tailroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *port100_alloc_skb(struct port100 *dev, unsigned int size)
{
	struct sk_buff *skb;

	skb = alloc_skb(dev->skb_headroom + dev->skb_tailroom + size,
			GFP_KERNEL);
	if (skb)
		skb_reserve(skb, dev->skb_headroom);

	return skb;
}