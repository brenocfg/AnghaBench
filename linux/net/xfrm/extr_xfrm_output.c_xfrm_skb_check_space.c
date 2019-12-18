#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct dst_entry {int header_len; TYPE_1__* dev; } ;
struct TYPE_2__ {int needed_tailroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LL_RESERVED_SPACE (TYPE_1__*) ; 
 int pskb_expand_head (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int skb_headroom (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int xfrm_skb_check_space(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	int nhead = dst->header_len + LL_RESERVED_SPACE(dst->dev)
		- skb_headroom(skb);
	int ntail = dst->dev->needed_tailroom - skb_tailroom(skb);

	if (nhead <= 0) {
		if (ntail <= 0)
			return 0;
		nhead = 0;
	} else if (ntail < 0)
		ntail = 0;

	return pskb_expand_head(skb, nhead, ntail, GFP_ATOMIC);
}