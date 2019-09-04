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
struct sock {TYPE_1__* sk_prot; int /*<<< orphan*/  sk_allocation; scalar_t__ sk_err; } ;
struct sk_buff {int dummy; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_rto; scalar_t__ icsk_retransmits; } ;
struct dst_entry {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_iss; int /*<<< orphan*/  dccps_gar; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_ACTIVEOPENS ; 
 int /*<<< orphan*/  DCCP_PKT_REQUEST ; 
 int /*<<< orphan*/  DCCP_RTO_MAX ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int ENOBUFS ; 
 int EPROTO ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_feat_finalise_settings (struct dccp_sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_skb_entail (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_transmit_skb (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int dccp_connect(struct sock *sk)
{
	struct sk_buff *skb;
	struct dccp_sock *dp = dccp_sk(sk);
	struct dst_entry *dst = __sk_dst_get(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);

	sk->sk_err = 0;
	sock_reset_flag(sk, SOCK_DONE);

	dccp_sync_mss(sk, dst_mtu(dst));

	/* do not connect if feature negotiation setup fails */
	if (dccp_feat_finalise_settings(dccp_sk(sk)))
		return -EPROTO;

	/* Initialise GAR as per 8.5; AWL/AWH are set in dccp_transmit_skb() */
	dp->dccps_gar = dp->dccps_iss;

	skb = alloc_skb(sk->sk_prot->max_header, sk->sk_allocation);
	if (unlikely(skb == NULL))
		return -ENOBUFS;

	/* Reserve space for headers. */
	skb_reserve(skb, sk->sk_prot->max_header);

	DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_REQUEST;

	dccp_transmit_skb(sk, dccp_skb_entail(sk, skb));
	DCCP_INC_STATS(DCCP_MIB_ACTIVEOPENS);

	/* Timer for repeating the REQUEST until an answer. */
	icsk->icsk_retransmits = 0;
	inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
				  icsk->icsk_rto, DCCP_RTO_MAX);
	return 0;
}