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
struct sk_buff {scalar_t__ csum; } ;
struct cxgbi_sock {struct sk_buff* wr_pending_head; } ;

/* Variables and functions */
 struct sk_buff* cxgbi_skcb_tx_wr_next (struct sk_buff const*) ; 

__attribute__((used)) static inline int cxgbi_sock_count_pending_wrs(const struct cxgbi_sock *csk)
{
	int n = 0;
	const struct sk_buff *skb = csk->wr_pending_head;

	while (skb) {
		n += skb->csum;
		skb = cxgbi_skcb_tx_wr_next(skb);
	}
	return n;
}