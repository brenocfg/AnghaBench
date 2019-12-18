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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* tcp_sacktag_bsearch (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *tcp_sacktag_skip(struct sk_buff *skb, struct sock *sk,
					u32 skip_to_seq)
{
	if (skb && after(TCP_SKB_CB(skb)->seq, skip_to_seq))
		return skb;

	return tcp_sacktag_bsearch(sk, skip_to_seq);
}