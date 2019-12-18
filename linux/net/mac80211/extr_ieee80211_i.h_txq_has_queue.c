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
struct TYPE_2__ {int /*<<< orphan*/  backlog_packets; } ;
struct txq_info {TYPE_1__ tin; int /*<<< orphan*/  frags; } ;
struct ieee80211_txq {int dummy; } ;

/* Variables and functions */
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 struct txq_info* to_txq_info (struct ieee80211_txq*) ; 

__attribute__((used)) static inline bool txq_has_queue(struct ieee80211_txq *txq)
{
	struct txq_info *txqi = to_txq_info(txq);

	return !(skb_queue_empty(&txqi->frags) && !txqi->tin.backlog_packets);
}