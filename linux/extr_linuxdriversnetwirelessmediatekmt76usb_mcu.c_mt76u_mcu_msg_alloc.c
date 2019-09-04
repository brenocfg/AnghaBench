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
 scalar_t__ MT_CMD_HDR_LEN ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void const*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

struct sk_buff *mt76u_mcu_msg_alloc(const void *data, int len)
{
	struct sk_buff *skb;

	skb = alloc_skb(MT_CMD_HDR_LEN + len + 8, GFP_KERNEL);
	if (!skb)
		return NULL;

	skb_reserve(skb, MT_CMD_HDR_LEN);
	skb_put_data(skb, data, len);

	return skb;
}