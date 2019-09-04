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
struct fq_tin {int dummy; } ;
struct txq_info {int /*<<< orphan*/  frags; struct fq_tin tin; } ;
struct fq {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; struct fq fq; } ;

/* Variables and functions */
 int /*<<< orphan*/  fq_skb_free_func ; 
 int /*<<< orphan*/  fq_tin_reset (struct fq*,struct fq_tin*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_purge_tx_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ieee80211_txq_purge(struct ieee80211_local *local,
			 struct txq_info *txqi)
{
	struct fq *fq = &local->fq;
	struct fq_tin *tin = &txqi->tin;

	fq_tin_reset(fq, tin, fq_skb_free_func);
	ieee80211_purge_tx_queue(&local->hw, &txqi->frags);
}