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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_skb_generic_pop(struct sk_buff *skb, u32 off, u32 len)
{
	/* skb_ensure_writable() is not needed here, as we're
	 * already working on an uncloned skb.
	 */
	if (unlikely(!pskb_may_pull(skb, off + len)))
		return -ENOMEM;

	skb_postpull_rcsum(skb, skb->data + off, len);
	memmove(skb->data + len, skb->data, off);
	__skb_pull(skb, len);

	return 0;
}