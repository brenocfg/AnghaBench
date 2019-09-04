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
struct sk_buff {unsigned int len; scalar_t__ data; } ;

/* Variables and functions */
 unsigned int L2PAD_SIZE (unsigned int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned int) ; 

void rt2x00queue_insert_l2pad(struct sk_buff *skb, unsigned int hdr_len)
{
	unsigned int l2pad = (skb->len > hdr_len) ? L2PAD_SIZE(hdr_len) : 0;

	if (!l2pad)
		return;

	skb_push(skb, l2pad);
	memmove(skb->data, skb->data + l2pad, hdr_len);
}