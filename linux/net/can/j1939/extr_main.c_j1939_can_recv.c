#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {int sa; int pgn; size_t da; int /*<<< orphan*/  type; } ;
struct j1939_sk_buff_cb {int priority; int /*<<< orphan*/  flags; TYPE_2__ addr; int /*<<< orphan*/  tskey; } ;
struct j1939_priv {int /*<<< orphan*/  lock; TYPE_1__* ents; } ;
struct can_frame {int can_id; int /*<<< orphan*/  can_dlc; } ;
struct TYPE_3__ {scalar_t__ nusers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  J1939_CAN_HDR ; 
 int /*<<< orphan*/  J1939_ECU_LOCAL_DST ; 
 int /*<<< orphan*/  J1939_ECU_LOCAL_SRC ; 
 size_t J1939_NO_ADDR ; 
 int J1939_PGN_MAX ; 
 int /*<<< orphan*/  J1939_TP ; 
 int /*<<< orphan*/  can_skb_set_owner (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_ac_recv (struct j1939_priv*,struct sk_buff*) ; 
 scalar_t__ j1939_address_is_unicast (size_t) ; 
 scalar_t__ j1939_pgn_is_pdu1 (int) ; 
 int /*<<< orphan*/  j1939_simple_recv (struct j1939_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  j1939_sk_recv (struct j1939_priv*,struct sk_buff*) ; 
 struct j1939_sk_buff_cb* j1939_skb_to_cb (struct sk_buff*) ; 
 scalar_t__ j1939_tp_recv (struct j1939_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct j1939_sk_buff_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint8_t ; 

__attribute__((used)) static void j1939_can_recv(struct sk_buff *iskb, void *data)
{
	struct j1939_priv *priv = data;
	struct sk_buff *skb;
	struct j1939_sk_buff_cb *skcb, *iskcb;
	struct can_frame *cf;

	/* create a copy of the skb
	 * j1939 only delivers the real data bytes,
	 * the header goes into sockaddr.
	 * j1939 may not touch the incoming skb in such way
	 */
	skb = skb_clone(iskb, GFP_ATOMIC);
	if (!skb)
		return;

	can_skb_set_owner(skb, iskb->sk);

	/* get a pointer to the header of the skb
	 * the skb payload (pointer) is moved, so that the next skb_data
	 * returns the actual payload
	 */
	cf = (void *)skb->data;
	skb_pull(skb, J1939_CAN_HDR);

	/* fix length, set to dlc, with 8 maximum */
	skb_trim(skb, min_t(uint8_t, cf->can_dlc, 8));

	/* set addr */
	skcb = j1939_skb_to_cb(skb);
	memset(skcb, 0, sizeof(*skcb));

	iskcb = j1939_skb_to_cb(iskb);
	skcb->tskey = iskcb->tskey;
	skcb->priority = (cf->can_id >> 26) & 0x7;
	skcb->addr.sa = cf->can_id;
	skcb->addr.pgn = (cf->can_id >> 8) & J1939_PGN_MAX;
	/* set default message type */
	skcb->addr.type = J1939_TP;
	if (j1939_pgn_is_pdu1(skcb->addr.pgn)) {
		/* Type 1: with destination address */
		skcb->addr.da = skcb->addr.pgn;
		/* normalize pgn: strip dst address */
		skcb->addr.pgn &= 0x3ff00;
	} else {
		/* set broadcast address */
		skcb->addr.da = J1939_NO_ADDR;
	}

	/* update localflags */
	read_lock_bh(&priv->lock);
	if (j1939_address_is_unicast(skcb->addr.sa) &&
	    priv->ents[skcb->addr.sa].nusers)
		skcb->flags |= J1939_ECU_LOCAL_SRC;
	if (j1939_address_is_unicast(skcb->addr.da) &&
	    priv->ents[skcb->addr.da].nusers)
		skcb->flags |= J1939_ECU_LOCAL_DST;
	read_unlock_bh(&priv->lock);

	/* deliver into the j1939 stack ... */
	j1939_ac_recv(priv, skb);

	if (j1939_tp_recv(priv, skb))
		/* this means the transport layer processed the message */
		goto done;

	j1939_simple_recv(priv, skb);
	j1939_sk_recv(priv, skb);
 done:
	kfree_skb(skb);
}