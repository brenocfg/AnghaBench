#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xdp_sock {scalar_t__ queue_id; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tx; TYPE_1__* dev; TYPE_2__* umem; } ;
struct xdp_desc {scalar_t__ addr; int /*<<< orphan*/  len; } ;
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_priority; } ;
struct sk_buff {int /*<<< orphan*/  destructor; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; TYPE_1__* dev; } ;
struct TYPE_7__ {void* destructor_arg; } ;
struct TYPE_6__ {int /*<<< orphan*/  cq; } ;
struct TYPE_5__ {scalar_t__ real_num_tx_queues; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int NETDEV_TX_BUSY ; 
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  TX_BATCH_SIZE ; 
 int dev_direct_xmit (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int skb_store_bits (struct sk_buff*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 char* xdp_umem_get_data (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xsk_destruct_skb ; 
 int /*<<< orphan*/  xskq_discard_desc (int /*<<< orphan*/ ) ; 
 scalar_t__ xskq_peek_desc (int /*<<< orphan*/ ,struct xdp_desc*,TYPE_2__*) ; 
 scalar_t__ xskq_reserve_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsk_generic_xmit(struct sock *sk)
{
	struct xdp_sock *xs = xdp_sk(sk);
	u32 max_batch = TX_BATCH_SIZE;
	bool sent_frame = false;
	struct xdp_desc desc;
	struct sk_buff *skb;
	int err = 0;

	mutex_lock(&xs->mutex);

	if (xs->queue_id >= xs->dev->real_num_tx_queues)
		goto out;

	while (xskq_peek_desc(xs->tx, &desc, xs->umem)) {
		char *buffer;
		u64 addr;
		u32 len;

		if (max_batch-- == 0) {
			err = -EAGAIN;
			goto out;
		}

		len = desc.len;
		skb = sock_alloc_send_skb(sk, len, 1, &err);
		if (unlikely(!skb)) {
			err = -EAGAIN;
			goto out;
		}

		skb_put(skb, len);
		addr = desc.addr;
		buffer = xdp_umem_get_data(xs->umem, addr);
		err = skb_store_bits(skb, 0, buffer, len);
		if (unlikely(err) || xskq_reserve_addr(xs->umem->cq)) {
			kfree_skb(skb);
			goto out;
		}

		skb->dev = xs->dev;
		skb->priority = sk->sk_priority;
		skb->mark = sk->sk_mark;
		skb_shinfo(skb)->destructor_arg = (void *)(long)desc.addr;
		skb->destructor = xsk_destruct_skb;

		err = dev_direct_xmit(skb, xs->queue_id);
		xskq_discard_desc(xs->tx);
		/* Ignore NET_XMIT_CN as packet might have been sent */
		if (err == NET_XMIT_DROP || err == NETDEV_TX_BUSY) {
			/* SKB completed but not sent */
			err = -EBUSY;
			goto out;
		}

		sent_frame = true;
	}

out:
	if (sent_frame)
		sk->sk_write_space(sk);

	mutex_unlock(&xs->mutex);
	return err;
}