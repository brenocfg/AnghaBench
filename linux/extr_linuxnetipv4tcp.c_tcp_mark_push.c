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
struct tcp_sock {int /*<<< orphan*/  write_seq; int /*<<< orphan*/  pushed_seq; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPHDR_PSH ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 

__attribute__((used)) static inline void tcp_mark_push(struct tcp_sock *tp, struct sk_buff *skb)
{
	TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_PSH;
	tp->pushed_seq = tp->write_seq;
}