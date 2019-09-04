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
struct xfrm_policy {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int pfkey_xfrm_policy2msg_size (struct xfrm_policy const*) ; 

__attribute__((used)) static struct sk_buff * pfkey_xfrm_policy2msg_prep(const struct xfrm_policy *xp)
{
	struct sk_buff *skb;
	int size;

	size = pfkey_xfrm_policy2msg_size(xp);

	skb =  alloc_skb(size + 16, GFP_ATOMIC);
	if (skb == NULL)
		return ERR_PTR(-ENOBUFS);

	return skb;
}