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
struct nlattr {int dummy; } ;
struct cfg80211_txq_stats {int filled; int /*<<< orphan*/  max_flows; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  collisions; int /*<<< orphan*/  overmemory; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  ecn_marks; int /*<<< orphan*/  drops; int /*<<< orphan*/  flows; int /*<<< orphan*/  backlog_packets; int /*<<< orphan*/  backlog_bytes; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_BACKLOG_BYTES ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_BACKLOG_PACKETS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_COLLISIONS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_DROPS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_ECN_MARKS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_FLOWS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_MAX_FLOWS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_OVERLIMIT ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_OVERMEMORY ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_TX_BYTES ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_TX_PACKETS ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nl80211_put_txq_stats(struct sk_buff *msg,
				  struct cfg80211_txq_stats *txqstats,
				  int attrtype)
{
	struct nlattr *txqattr;

#define PUT_TXQVAL_U32(attr, memb) do {					  \
	if (txqstats->filled & BIT(NL80211_TXQ_STATS_ ## attr) &&	  \
	    nla_put_u32(msg, NL80211_TXQ_STATS_ ## attr, txqstats->memb)) \
		return false;						  \
	} while (0)

	txqattr = nla_nest_start(msg, attrtype);
	if (!txqattr)
		return false;

	PUT_TXQVAL_U32(BACKLOG_BYTES, backlog_bytes);
	PUT_TXQVAL_U32(BACKLOG_PACKETS, backlog_packets);
	PUT_TXQVAL_U32(FLOWS, flows);
	PUT_TXQVAL_U32(DROPS, drops);
	PUT_TXQVAL_U32(ECN_MARKS, ecn_marks);
	PUT_TXQVAL_U32(OVERLIMIT, overlimit);
	PUT_TXQVAL_U32(OVERMEMORY, overmemory);
	PUT_TXQVAL_U32(COLLISIONS, collisions);
	PUT_TXQVAL_U32(TX_BYTES, tx_bytes);
	PUT_TXQVAL_U32(TX_PACKETS, tx_packets);
	PUT_TXQVAL_U32(MAX_FLOWS, max_flows);
	nla_nest_end(msg, txqattr);

#undef PUT_TXQVAL_U32
	return true;
}