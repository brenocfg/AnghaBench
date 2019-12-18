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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct l2tp_tunnel {int /*<<< orphan*/  peer_tunnel_id; int /*<<< orphan*/  tunnel_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_oos_packets; int /*<<< orphan*/  rx_seq_discards; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct l2tp_session {int recv_seq; int send_seq; int lns_mode; TYPE_1__ stats; scalar_t__ reorder_timeout; int /*<<< orphan*/ * peer_cookie; scalar_t__ peer_cookie_len; int /*<<< orphan*/ * cookie; scalar_t__ cookie_len; scalar_t__* ifname; int /*<<< orphan*/  pwtype; int /*<<< orphan*/  debug; int /*<<< orphan*/  peer_session_id; int /*<<< orphan*/  session_id; struct l2tp_tunnel* tunnel; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  L2TP_ATTR_CONN_ID ; 
 int /*<<< orphan*/  L2TP_ATTR_COOKIE ; 
 int /*<<< orphan*/  L2TP_ATTR_DEBUG ; 
 int /*<<< orphan*/  L2TP_ATTR_IFNAME ; 
 int /*<<< orphan*/  L2TP_ATTR_LNS_MODE ; 
 int /*<<< orphan*/  L2TP_ATTR_PAD ; 
 int /*<<< orphan*/  L2TP_ATTR_PEER_CONN_ID ; 
 int /*<<< orphan*/  L2TP_ATTR_PEER_COOKIE ; 
 int /*<<< orphan*/  L2TP_ATTR_PEER_SESSION_ID ; 
 int /*<<< orphan*/  L2TP_ATTR_PW_TYPE ; 
 int /*<<< orphan*/  L2TP_ATTR_RECV_SEQ ; 
 int /*<<< orphan*/  L2TP_ATTR_RECV_TIMEOUT ; 
 int /*<<< orphan*/  L2TP_ATTR_RX_BYTES ; 
 int /*<<< orphan*/  L2TP_ATTR_RX_ERRORS ; 
 int /*<<< orphan*/  L2TP_ATTR_RX_OOS_PACKETS ; 
 int /*<<< orphan*/  L2TP_ATTR_RX_PACKETS ; 
 int /*<<< orphan*/  L2TP_ATTR_RX_SEQ_DISCARDS ; 
 int /*<<< orphan*/  L2TP_ATTR_SEND_SEQ ; 
 int /*<<< orphan*/  L2TP_ATTR_SESSION_ID ; 
 int /*<<< orphan*/  L2TP_ATTR_STATS ; 
 int /*<<< orphan*/  L2TP_ATTR_STATS_PAD ; 
 int /*<<< orphan*/  L2TP_ATTR_TX_BYTES ; 
 int /*<<< orphan*/  L2TP_ATTR_TX_ERRORS ; 
 int /*<<< orphan*/  L2TP_ATTR_TX_PACKETS ; 
 int /*<<< orphan*/  L2TP_ATTR_USING_IPSEC ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_nl_family ; 
 scalar_t__ l2tp_tunnel_uses_xfrm (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_msecs (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int l2tp_nl_session_send(struct sk_buff *skb, u32 portid, u32 seq, int flags,
				struct l2tp_session *session, u8 cmd)
{
	void *hdr;
	struct nlattr *nest;
	struct l2tp_tunnel *tunnel = session->tunnel;

	hdr = genlmsg_put(skb, portid, seq, &l2tp_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	if (nla_put_u32(skb, L2TP_ATTR_CONN_ID, tunnel->tunnel_id) ||
	    nla_put_u32(skb, L2TP_ATTR_SESSION_ID, session->session_id) ||
	    nla_put_u32(skb, L2TP_ATTR_PEER_CONN_ID, tunnel->peer_tunnel_id) ||
	    nla_put_u32(skb, L2TP_ATTR_PEER_SESSION_ID,
			session->peer_session_id) ||
	    nla_put_u32(skb, L2TP_ATTR_DEBUG, session->debug) ||
	    nla_put_u16(skb, L2TP_ATTR_PW_TYPE, session->pwtype))
		goto nla_put_failure;

	if ((session->ifname[0] &&
	     nla_put_string(skb, L2TP_ATTR_IFNAME, session->ifname)) ||
	    (session->cookie_len &&
	     nla_put(skb, L2TP_ATTR_COOKIE, session->cookie_len,
		     &session->cookie[0])) ||
	    (session->peer_cookie_len &&
	     nla_put(skb, L2TP_ATTR_PEER_COOKIE, session->peer_cookie_len,
		     &session->peer_cookie[0])) ||
	    nla_put_u8(skb, L2TP_ATTR_RECV_SEQ, session->recv_seq) ||
	    nla_put_u8(skb, L2TP_ATTR_SEND_SEQ, session->send_seq) ||
	    nla_put_u8(skb, L2TP_ATTR_LNS_MODE, session->lns_mode) ||
	    (l2tp_tunnel_uses_xfrm(tunnel) &&
	     nla_put_u8(skb, L2TP_ATTR_USING_IPSEC, 1)) ||
	    (session->reorder_timeout &&
	     nla_put_msecs(skb, L2TP_ATTR_RECV_TIMEOUT,
			   session->reorder_timeout, L2TP_ATTR_PAD)))
		goto nla_put_failure;

	nest = nla_nest_start_noflag(skb, L2TP_ATTR_STATS);
	if (nest == NULL)
		goto nla_put_failure;

	if (nla_put_u64_64bit(skb, L2TP_ATTR_TX_PACKETS,
			      atomic_long_read(&session->stats.tx_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_TX_BYTES,
			      atomic_long_read(&session->stats.tx_bytes),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_TX_ERRORS,
			      atomic_long_read(&session->stats.tx_errors),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_PACKETS,
			      atomic_long_read(&session->stats.rx_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_BYTES,
			      atomic_long_read(&session->stats.rx_bytes),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_SEQ_DISCARDS,
			      atomic_long_read(&session->stats.rx_seq_discards),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_OOS_PACKETS,
			      atomic_long_read(&session->stats.rx_oos_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_ERRORS,
			      atomic_long_read(&session->stats.rx_errors),
			      L2TP_ATTR_STATS_PAD))
		goto nla_put_failure;
	nla_nest_end(skb, nest);

	genlmsg_end(skb, hdr);
	return 0;

 nla_put_failure:
	genlmsg_cancel(skb, hdr);
	return -1;
}