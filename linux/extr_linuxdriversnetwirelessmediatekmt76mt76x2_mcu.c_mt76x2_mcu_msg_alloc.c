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
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *mt76x2_mcu_msg_alloc(const void *data, int len)
{
	struct sk_buff *skb;

	skb = alloc_skb(len, GFP_KERNEL);
	if (!skb)
		return NULL;
	memcpy(skb_put(skb, len), data, len);

	return skb;
}