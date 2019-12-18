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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static bool enlarge_skb(struct sk_buff *skb, unsigned int extra)
{
	if (skb->len + extra > 65535)
		return false;

	if (pskb_expand_head(skb, 0, extra - skb_tailroom(skb), GFP_ATOMIC))
		return false;

	return true;
}