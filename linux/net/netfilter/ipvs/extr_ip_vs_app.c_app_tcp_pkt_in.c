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
struct tcphdr {int /*<<< orphan*/  seq; } ;
struct sk_buff {int dummy; } ;
struct ip_vs_iphdr {int dummy; } ;
struct ip_vs_conn {int flags; int /*<<< orphan*/  in_seq; int /*<<< orphan*/  out_seq; } ;
struct ip_vs_app {int /*<<< orphan*/  (* pkt_in ) (struct ip_vs_app*,struct ip_vs_conn*,struct sk_buff*,int*,struct ip_vs_iphdr*) ;} ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int IP_VS_CONN_F_IN_SEQ ; 
 int IP_VS_CONN_F_OUT_SEQ ; 
 unsigned int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int const) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_app*,struct ip_vs_conn*,struct sk_buff*,int*,struct ip_vs_iphdr*) ; 
 int /*<<< orphan*/  vs_fix_ack_seq (int /*<<< orphan*/ *,struct tcphdr*) ; 
 int /*<<< orphan*/  vs_fix_seq (int /*<<< orphan*/ *,struct tcphdr*) ; 
 int /*<<< orphan*/  vs_seq_update (struct ip_vs_conn*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int app_tcp_pkt_in(struct ip_vs_conn *cp, struct sk_buff *skb,
				 struct ip_vs_app *app,
				 struct ip_vs_iphdr *ipvsh)
{
	int diff;
	const unsigned int tcp_offset = ip_hdrlen(skb);
	struct tcphdr *th;
	__u32 seq;

	if (skb_ensure_writable(skb, tcp_offset + sizeof(*th)))
		return 0;

	th = (struct tcphdr *)(skb_network_header(skb) + tcp_offset);

	/*
	 *	Remember seq number in case this pkt gets resized
	 */
	seq = ntohl(th->seq);

	/*
	 *	Fix seq stuff if flagged as so.
	 */
	if (cp->flags & IP_VS_CONN_F_IN_SEQ)
		vs_fix_seq(&cp->in_seq, th);
	if (cp->flags & IP_VS_CONN_F_OUT_SEQ)
		vs_fix_ack_seq(&cp->out_seq, th);

	/*
	 *	Call private input hook function
	 */
	if (app->pkt_in == NULL)
		return 1;

	if (!app->pkt_in(app, cp, skb, &diff, ipvsh))
		return 0;

	/*
	 *	Update ip_vs seq stuff if len has changed.
	 */
	if (diff != 0)
		vs_seq_update(cp, &cp->in_seq,
			      IP_VS_CONN_F_IN_SEQ, seq, diff);

	return 1;
}