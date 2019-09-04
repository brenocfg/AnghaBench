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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;
struct smap_psock {int /*<<< orphan*/  ingress; struct sock* sock; } ;
struct sk_msg_buff {int sg_end; int /*<<< orphan*/  list; struct sk_buff* skb; scalar_t__ sg_start; int /*<<< orphan*/  sg_data; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 int EAGAIN ; 
 int GFP_ATOMIC ; 
 int MAX_SKB_FRAGS ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  kfree (struct sk_msg_buff*) ; 
 struct sk_msg_buff* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,int) ; 
 int /*<<< orphan*/  sk_rmem_schedule (struct sock*,struct sk_buff*,int) ; 
 int skb_to_sgvec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smap_do_ingress(struct smap_psock *psock, struct sk_buff *skb)
{
	struct sock *sk = psock->sock;
	int copied = 0, num_sg;
	struct sk_msg_buff *r;

	r = kzalloc(sizeof(struct sk_msg_buff), __GFP_NOWARN | GFP_ATOMIC);
	if (unlikely(!r))
		return -EAGAIN;

	if (!sk_rmem_schedule(sk, skb, skb->len)) {
		kfree(r);
		return -EAGAIN;
	}

	sg_init_table(r->sg_data, MAX_SKB_FRAGS);
	num_sg = skb_to_sgvec(skb, r->sg_data, 0, skb->len);
	if (unlikely(num_sg < 0)) {
		kfree(r);
		return num_sg;
	}
	sk_mem_charge(sk, skb->len);
	copied = skb->len;
	r->sg_start = 0;
	r->sg_end = num_sg == MAX_SKB_FRAGS ? 0 : num_sg;
	r->skb = skb;
	list_add_tail(&r->list, &psock->ingress);
	sk->sk_data_ready(sk);
	return copied;
}