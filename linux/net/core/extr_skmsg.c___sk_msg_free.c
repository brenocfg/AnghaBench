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
struct TYPE_2__ {scalar_t__ size; } ;
struct sk_msg {int /*<<< orphan*/  skb; TYPE_1__ sg; } ;
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_msg_check_to_free (struct sk_msg*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_msg_free_elem (struct sock*,struct sk_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_msg_init (struct sk_msg*) ; 
 int /*<<< orphan*/  sk_msg_iter_var_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __sk_msg_free(struct sock *sk, struct sk_msg *msg, u32 i,
			 bool charge)
{
	struct scatterlist *sge = sk_msg_elem(msg, i);
	int freed = 0;

	while (msg->sg.size) {
		msg->sg.size -= sge->length;
		freed += sk_msg_free_elem(sk, msg, i, charge);
		sk_msg_iter_var_next(i);
		sk_msg_check_to_free(msg, i, msg->sg.size);
		sge = sk_msg_elem(msg, i);
	}
	consume_skb(msg->skb);
	sk_msg_init(msg);
	return freed;
}