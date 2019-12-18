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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_stats {int recv_fragments; int recv_fragmented; int recv_bundles; int recv_bundled; int sent_fragments; int sent_fragmented; int sent_bundles; int sent_bundled; int msg_length_counts; int msg_lengths_total; int* msg_length_profile; int recv_states; int recv_probes; int recv_nacks; int deferred_recv; int sent_states; int sent_probes; int sent_nacks; int sent_acks; int retransmitted; int duplicates; int link_congs; int max_queue_sz; int queue_sz_counts; int accu_queue_sz; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nla_map*) ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_STATS ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_AVG_QUEUE ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_DUPLICATES ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_LINK_CONGS ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MAX_QUEUE ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_CNT ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_P0 ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_P1 ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_P2 ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_P3 ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_P4 ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_P5 ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_P6 ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_LEN_TOT ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_MSG_PROF_TOT ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RETRANSMITTED ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_BUNDLED ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_BUNDLES ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_DEFERRED ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_FRAGMENTED ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_FRAGMENTS ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_INFO ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_NACKS ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_PROBES ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_RX_STATES ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_ACKS ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_BUNDLED ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_BUNDLES ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_FRAGMENTED ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_FRAGMENTS ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_INFO ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_NACKS ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_PROBES ; 
 int /*<<< orphan*/  TIPC_NLA_STATS_TX_STATES ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __tipc_nl_add_stats(struct sk_buff *skb, struct tipc_stats *s)
{
	int i;
	struct nlattr *stats;

	struct nla_map {
		u32 key;
		u32 val;
	};

	struct nla_map map[] = {
		{TIPC_NLA_STATS_RX_INFO, 0},
		{TIPC_NLA_STATS_RX_FRAGMENTS, s->recv_fragments},
		{TIPC_NLA_STATS_RX_FRAGMENTED, s->recv_fragmented},
		{TIPC_NLA_STATS_RX_BUNDLES, s->recv_bundles},
		{TIPC_NLA_STATS_RX_BUNDLED, s->recv_bundled},
		{TIPC_NLA_STATS_TX_INFO, 0},
		{TIPC_NLA_STATS_TX_FRAGMENTS, s->sent_fragments},
		{TIPC_NLA_STATS_TX_FRAGMENTED, s->sent_fragmented},
		{TIPC_NLA_STATS_TX_BUNDLES, s->sent_bundles},
		{TIPC_NLA_STATS_TX_BUNDLED, s->sent_bundled},
		{TIPC_NLA_STATS_MSG_PROF_TOT, (s->msg_length_counts) ?
			s->msg_length_counts : 1},
		{TIPC_NLA_STATS_MSG_LEN_CNT, s->msg_length_counts},
		{TIPC_NLA_STATS_MSG_LEN_TOT, s->msg_lengths_total},
		{TIPC_NLA_STATS_MSG_LEN_P0, s->msg_length_profile[0]},
		{TIPC_NLA_STATS_MSG_LEN_P1, s->msg_length_profile[1]},
		{TIPC_NLA_STATS_MSG_LEN_P2, s->msg_length_profile[2]},
		{TIPC_NLA_STATS_MSG_LEN_P3, s->msg_length_profile[3]},
		{TIPC_NLA_STATS_MSG_LEN_P4, s->msg_length_profile[4]},
		{TIPC_NLA_STATS_MSG_LEN_P5, s->msg_length_profile[5]},
		{TIPC_NLA_STATS_MSG_LEN_P6, s->msg_length_profile[6]},
		{TIPC_NLA_STATS_RX_STATES, s->recv_states},
		{TIPC_NLA_STATS_RX_PROBES, s->recv_probes},
		{TIPC_NLA_STATS_RX_NACKS, s->recv_nacks},
		{TIPC_NLA_STATS_RX_DEFERRED, s->deferred_recv},
		{TIPC_NLA_STATS_TX_STATES, s->sent_states},
		{TIPC_NLA_STATS_TX_PROBES, s->sent_probes},
		{TIPC_NLA_STATS_TX_NACKS, s->sent_nacks},
		{TIPC_NLA_STATS_TX_ACKS, s->sent_acks},
		{TIPC_NLA_STATS_RETRANSMITTED, s->retransmitted},
		{TIPC_NLA_STATS_DUPLICATES, s->duplicates},
		{TIPC_NLA_STATS_LINK_CONGS, s->link_congs},
		{TIPC_NLA_STATS_MAX_QUEUE, s->max_queue_sz},
		{TIPC_NLA_STATS_AVG_QUEUE, s->queue_sz_counts ?
			(s->accu_queue_sz / s->queue_sz_counts) : 0}
	};

	stats = nla_nest_start_noflag(skb, TIPC_NLA_LINK_STATS);
	if (!stats)
		return -EMSGSIZE;

	for (i = 0; i <  ARRAY_SIZE(map); i++)
		if (nla_put_u32(skb, map[i].key, map[i].val))
			goto msg_full;

	nla_nest_end(skb, stats);

	return 0;
msg_full:
	nla_nest_cancel(skb, stats);

	return -EMSGSIZE;
}