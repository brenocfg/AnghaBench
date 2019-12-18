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
struct j1939_sk_buff_cb {int /*<<< orphan*/  addr; } ;
struct j1939_session {int dummy; } ;
struct j1939_priv {int dummy; } ;

/* Variables and functions */
 struct j1939_session* j1939_session_get_by_addr (struct j1939_priv*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  j1939_session_put (struct j1939_session*) ; 
 struct j1939_sk_buff_cb* j1939_skb_to_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  j1939_xtp_rx_cts_one (struct j1939_session*,struct sk_buff*) ; 

__attribute__((used)) static void
j1939_xtp_rx_cts(struct j1939_priv *priv, struct sk_buff *skb, bool transmitter)
{
	struct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	struct j1939_session *session;

	session = j1939_session_get_by_addr(priv, &skcb->addr, true,
					    transmitter);
	if (!session)
		return;
	j1939_xtp_rx_cts_one(session, skb);
	j1939_session_put(session);
}