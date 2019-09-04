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
struct TYPE_2__ {struct sock* sk_redir; } ;
struct tcp_skb_cb {TYPE_1__ bpf; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct tcp_skb_cb* TCP_SKB_CB (struct sk_buff*) ; 

struct sock *do_sk_redirect_map(struct sk_buff *skb)
{
	struct tcp_skb_cb *tcb = TCP_SKB_CB(skb);

	return tcb->bpf.sk_redir;
}