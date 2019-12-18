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
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  collisions; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  flows; int /*<<< orphan*/  backlog_packets; int /*<<< orphan*/  backlog_bytes; } ;
struct TYPE_3__ {int /*<<< orphan*/  ecn_mark; int /*<<< orphan*/  drop_count; } ;
struct txq_info {TYPE_2__ tin; TYPE_1__ cstats; } ;
struct cfg80211_txq_stats {int filled; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  collisions; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  ecn_marks; int /*<<< orphan*/  drops; int /*<<< orphan*/  flows; int /*<<< orphan*/  backlog_packets; int /*<<< orphan*/  backlog_bytes; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_BACKLOG_BYTES ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_BACKLOG_PACKETS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_COLLISIONS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_DROPS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_ECN_MARKS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_FLOWS ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_OVERLIMIT ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_TX_BYTES ; 
 int /*<<< orphan*/  NL80211_TXQ_STATS_TX_PACKETS ; 

void ieee80211_fill_txq_stats(struct cfg80211_txq_stats *txqstats,
			      struct txq_info *txqi)
{
	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_BACKLOG_BYTES))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_BACKLOG_BYTES);
		txqstats->backlog_bytes = txqi->tin.backlog_bytes;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_BACKLOG_PACKETS))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_BACKLOG_PACKETS);
		txqstats->backlog_packets = txqi->tin.backlog_packets;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_FLOWS))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_FLOWS);
		txqstats->flows = txqi->tin.flows;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_DROPS))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_DROPS);
		txqstats->drops = txqi->cstats.drop_count;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_ECN_MARKS))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_ECN_MARKS);
		txqstats->ecn_marks = txqi->cstats.ecn_mark;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_OVERLIMIT))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_OVERLIMIT);
		txqstats->overlimit = txqi->tin.overlimit;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_COLLISIONS))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_COLLISIONS);
		txqstats->collisions = txqi->tin.collisions;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_TX_BYTES))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_TX_BYTES);
		txqstats->tx_bytes = txqi->tin.tx_bytes;
	}

	if (!(txqstats->filled & BIT(NL80211_TXQ_STATS_TX_PACKETS))) {
		txqstats->filled |= BIT(NL80211_TXQ_STATS_TX_PACKETS);
		txqstats->tx_packets = txqi->tin.tx_packets;
	}
}