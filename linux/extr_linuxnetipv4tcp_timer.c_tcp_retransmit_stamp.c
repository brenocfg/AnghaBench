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
struct TYPE_2__ {int /*<<< orphan*/  retrans_stamp; } ;

/* Variables and functions */
 struct sk_buff* tcp_rtx_queue_head (struct sock const*) ; 
 TYPE_1__* tcp_sk (struct sock const*) ; 
 int /*<<< orphan*/  tcp_skb_timestamp (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 tcp_retransmit_stamp(const struct sock *sk)
{
	u32 start_ts = tcp_sk(sk)->retrans_stamp;

	if (unlikely(!start_ts)) {
		struct sk_buff *head = tcp_rtx_queue_head(sk);

		if (!head)
			return 0;
		start_ts = tcp_skb_timestamp(head);
	}
	return start_ts;
}