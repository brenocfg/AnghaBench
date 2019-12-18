#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_4__* sk; } ;
struct TYPE_6__ {scalar_t__ pgn; scalar_t__ type; size_t da; } ;
struct j1939_sk_buff_cb {scalar_t__ tskey; TYPE_2__ addr; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {size_t total; int block; size_t last; } ;
struct j1939_session {int transmission; scalar_t__ tskey; TYPE_4__* sk; TYPE_3__ pkt; struct j1939_sk_buff_cb skcb; } ;
struct j1939_priv {size_t tp_max_packet_size; TYPE_1__* ents; } ;
struct TYPE_8__ {int /*<<< orphan*/  sk_tskey; } ;
struct TYPE_5__ {scalar_t__ nusers; } ;

/* Variables and functions */
 int EDESTADDRREQ ; 
 int EDOM ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 struct j1939_session* ERR_PTR (int) ; 
 int /*<<< orphan*/  J1939_ECU_LOCAL_DST ; 
 int /*<<< orphan*/  J1939_ECU_LOCAL_SRC ; 
 scalar_t__ J1939_ETP ; 
 scalar_t__ J1939_ETP_PGN_CTL ; 
 scalar_t__ J1939_ETP_PGN_DAT ; 
 size_t J1939_MAX_TP_PACKET_SIZE ; 
 scalar_t__ J1939_SIMPLE ; 
 scalar_t__ J1939_TP ; 
 scalar_t__ J1939_TP_PGN_CTL ; 
 scalar_t__ J1939_TP_PGN_DAT ; 
 int j1939_ac_fixup (struct j1939_priv*,struct sk_buff*) ; 
 scalar_t__ j1939_address_is_unicast (size_t) ; 
 scalar_t__ j1939_cb_is_broadcast (struct j1939_sk_buff_cb*) ; 
 struct j1939_session* j1939_session_new (struct j1939_priv*,struct sk_buff*,size_t) ; 
 struct j1939_sk_buff_cb* j1939_skb_to_cb (struct sk_buff*) ; 
 scalar_t__ j1939_tp_block ; 
 int min (int,size_t) ; 
 scalar_t__ unlikely (int) ; 

struct j1939_session *j1939_tp_send(struct j1939_priv *priv,
				    struct sk_buff *skb, size_t size)
{
	struct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	struct j1939_session *session;
	int ret;

	if (skcb->addr.pgn == J1939_TP_PGN_DAT ||
	    skcb->addr.pgn == J1939_TP_PGN_CTL ||
	    skcb->addr.pgn == J1939_ETP_PGN_DAT ||
	    skcb->addr.pgn == J1939_ETP_PGN_CTL)
		/* avoid conflict */
		return ERR_PTR(-EDOM);

	if (size > priv->tp_max_packet_size)
		return ERR_PTR(-EMSGSIZE);

	if (size <= 8)
		skcb->addr.type = J1939_SIMPLE;
	else if (size > J1939_MAX_TP_PACKET_SIZE)
		skcb->addr.type = J1939_ETP;
	else
		skcb->addr.type = J1939_TP;

	if (skcb->addr.type == J1939_ETP &&
	    j1939_cb_is_broadcast(skcb))
		return ERR_PTR(-EDESTADDRREQ);

	/* fill in addresses from names */
	ret = j1939_ac_fixup(priv, skb);
	if (unlikely(ret))
		return ERR_PTR(ret);

	/* fix DST flags, it may be used there soon */
	if (j1939_address_is_unicast(skcb->addr.da) &&
	    priv->ents[skcb->addr.da].nusers)
		skcb->flags |= J1939_ECU_LOCAL_DST;

	/* src is always local, I'm sending ... */
	skcb->flags |= J1939_ECU_LOCAL_SRC;

	/* prepare new session */
	session = j1939_session_new(priv, skb, size);
	if (!session)
		return ERR_PTR(-ENOMEM);

	/* skb is recounted in j1939_session_new() */
	session->sk = skb->sk;
	session->transmission = true;
	session->pkt.total = (size + 6) / 7;
	session->pkt.block = skcb->addr.type == J1939_ETP ? 255 :
		min(j1939_tp_block ?: 255, session->pkt.total);

	if (j1939_cb_is_broadcast(&session->skcb))
		/* set the end-packet for broadcast */
		session->pkt.last = session->pkt.total;

	skcb->tskey = session->sk->sk_tskey++;
	session->tskey = skcb->tskey;

	return session;
}