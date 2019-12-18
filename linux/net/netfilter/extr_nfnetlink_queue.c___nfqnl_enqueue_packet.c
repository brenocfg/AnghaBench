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
struct sk_buff {int dummy; } ;
struct nfqnl_instance {scalar_t__ queue_total; scalar_t__ queue_maxlen; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue_user_dropped; int /*<<< orphan*/  peer_portid; scalar_t__ id_sequence; int /*<<< orphan*/  queue_dropped; } ;
struct nf_queue_entry {scalar_t__ id; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int NFQA_CFG_F_FAIL_OPEN ; 
 int /*<<< orphan*/  NF_ACCEPT ; 
 int /*<<< orphan*/  __enqueue_entry (struct nfqnl_instance*,struct nf_queue_entry*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,scalar_t__) ; 
 scalar_t__ nf_ct_drop_unconfirmed (struct nf_queue_entry*) ; 
 int nfnetlink_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nfqnl_build_packet_message (struct net*,struct nfqnl_instance*,struct nf_queue_entry*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nfqnl_reinject (struct nf_queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__nfqnl_enqueue_packet(struct net *net, struct nfqnl_instance *queue,
			struct nf_queue_entry *entry)
{
	struct sk_buff *nskb;
	int err = -ENOBUFS;
	__be32 *packet_id_ptr;
	int failopen = 0;

	nskb = nfqnl_build_packet_message(net, queue, entry, &packet_id_ptr);
	if (nskb == NULL) {
		err = -ENOMEM;
		goto err_out;
	}
	spin_lock_bh(&queue->lock);

	if (nf_ct_drop_unconfirmed(entry))
		goto err_out_free_nskb;

	if (queue->queue_total >= queue->queue_maxlen) {
		if (queue->flags & NFQA_CFG_F_FAIL_OPEN) {
			failopen = 1;
			err = 0;
		} else {
			queue->queue_dropped++;
			net_warn_ratelimited("nf_queue: full at %d entries, dropping packets(s)\n",
					     queue->queue_total);
		}
		goto err_out_free_nskb;
	}
	entry->id = ++queue->id_sequence;
	*packet_id_ptr = htonl(entry->id);

	/* nfnetlink_unicast will either free the nskb or add it to a socket */
	err = nfnetlink_unicast(nskb, net, queue->peer_portid, MSG_DONTWAIT);
	if (err < 0) {
		if (queue->flags & NFQA_CFG_F_FAIL_OPEN) {
			failopen = 1;
			err = 0;
		} else {
			queue->queue_user_dropped++;
		}
		goto err_out_unlock;
	}

	__enqueue_entry(queue, entry);

	spin_unlock_bh(&queue->lock);
	return 0;

err_out_free_nskb:
	kfree_skb(nskb);
err_out_unlock:
	spin_unlock_bh(&queue->lock);
	if (failopen)
		nfqnl_reinject(entry, NF_ACCEPT);
err_out:
	return err;
}