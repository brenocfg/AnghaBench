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
struct sock {int /*<<< orphan*/  tcp_rtx_queue; } ;
struct sk_buff {int dummy; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  sk_wmem_free_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_rtx_queue_unlink (struct sk_buff*,struct sock*) ; 

__attribute__((used)) static void tcp_rtx_queue_purge(struct sock *sk)
{
	struct rb_node *p = rb_first(&sk->tcp_rtx_queue);

	while (p) {
		struct sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);
		/* Since we are deleting whole queue, no need to
		 * list_del(&skb->tcp_tsorted_anchor)
		 */
		tcp_rtx_queue_unlink(skb, sk);
		sk_wmem_free_skb(sk, skb);
	}
}