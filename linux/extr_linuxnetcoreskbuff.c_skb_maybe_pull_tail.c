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
struct sk_buff {unsigned int len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/ * __pskb_pull_tail (struct sk_buff*,unsigned int) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 

__attribute__((used)) static int skb_maybe_pull_tail(struct sk_buff *skb, unsigned int len,
			       unsigned int max)
{
	if (skb_headlen(skb) >= len)
		return 0;

	/* If we need to pullup then pullup to the max, so we
	 * won't need to do it again.
	 */
	if (max > skb->len)
		max = skb->len;

	if (__pskb_pull_tail(skb, max - skb_headlen(skb)) == NULL)
		return -ENOMEM;

	if (skb_headlen(skb) < len)
		return -EPROTO;

	return 0;
}