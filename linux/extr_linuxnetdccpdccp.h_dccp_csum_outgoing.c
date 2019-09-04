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
struct sk_buff {unsigned int len; int /*<<< orphan*/  csum; } ;
struct TYPE_2__ {scalar_t__ dccph_cscov; } ;

/* Variables and functions */
 unsigned int dccp_csum_coverage (struct sk_buff*) ; 
 TYPE_1__* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dccp_csum_outgoing(struct sk_buff *skb)
{
	unsigned int cov = dccp_csum_coverage(skb);

	if (cov >= skb->len)
		dccp_hdr(skb)->dccph_cscov = 0;

	skb->csum = skb_checksum(skb, 0, (cov > skb->len)? skb->len : cov, 0);
}