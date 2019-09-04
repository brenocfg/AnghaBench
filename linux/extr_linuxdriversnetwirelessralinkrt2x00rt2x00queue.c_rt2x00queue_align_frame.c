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
 unsigned int ALIGN_SIZE (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,unsigned int) ; 

void rt2x00queue_align_frame(struct sk_buff *skb)
{
	unsigned int frame_length = skb->len;
	unsigned int align = ALIGN_SIZE(skb, 0);

	if (!align)
		return;

	skb_push(skb, align);
	memmove(skb->data, skb->data + align, frame_length);
	skb_trim(skb, frame_length);
}