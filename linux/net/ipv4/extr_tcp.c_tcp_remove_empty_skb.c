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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CHRONO_BUSY ; 
 int /*<<< orphan*/  sk_wmem_free_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_chrono_stop (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_unlink_write_queue (struct sk_buff*,struct sock*) ; 
 scalar_t__ tcp_write_queue_empty (struct sock*) ; 

__attribute__((used)) static void tcp_remove_empty_skb(struct sock *sk, struct sk_buff *skb)
{
	if (skb && !skb->len) {
		tcp_unlink_write_queue(skb, sk);
		if (tcp_write_queue_empty(sk))
			tcp_chrono_stop(sk, TCP_CHRONO_BUSY);
		sk_wmem_free_skb(sk, skb);
	}
}