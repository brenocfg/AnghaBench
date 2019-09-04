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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int __skb_to_sgvec (struct sk_buff*,struct scatterlist*,int,int,int /*<<< orphan*/ ) ; 

int skb_to_sgvec_nomark(struct sk_buff *skb, struct scatterlist *sg,
			int offset, int len)
{
	return __skb_to_sgvec(skb, sg, offset, len, 0);
}