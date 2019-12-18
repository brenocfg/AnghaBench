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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int SKBTX_SHARED_FRAG ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_split_inside_header (struct sk_buff*,struct sk_buff*,int const,int) ; 
 int /*<<< orphan*/  skb_split_no_header (struct sk_buff*,struct sk_buff*,int const,int) ; 
 int /*<<< orphan*/  skb_zerocopy_clone (struct sk_buff*,struct sk_buff*,int /*<<< orphan*/ ) ; 

void skb_split(struct sk_buff *skb, struct sk_buff *skb1, const u32 len)
{
	int pos = skb_headlen(skb);

	skb_shinfo(skb1)->tx_flags |= skb_shinfo(skb)->tx_flags &
				      SKBTX_SHARED_FRAG;
	skb_zerocopy_clone(skb1, skb, 0);
	if (len < pos)	/* Split line is inside header. */
		skb_split_inside_header(skb, skb1, len, pos);
	else		/* Second chunk has no header, nothing to copy. */
		skb_split_no_header(skb, skb1, len, pos);
}