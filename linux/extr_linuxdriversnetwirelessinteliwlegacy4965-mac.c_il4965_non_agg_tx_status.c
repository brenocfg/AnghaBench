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
typedef  int /*<<< orphan*/  u8 ;
struct il_station_priv {int /*<<< orphan*/  pending_frames; scalar_t__ client; } ;
struct il_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/  vif; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* ieee80211_find_sta (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ieee80211_sta_block_awake (int /*<<< orphan*/ ,struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void
il4965_non_agg_tx_status(struct il_priv *il, const u8 *addr1)
{
	struct ieee80211_sta *sta;
	struct il_station_priv *sta_priv;

	rcu_read_lock();
	sta = ieee80211_find_sta(il->vif, addr1);
	if (sta) {
		sta_priv = (void *)sta->drv_priv;
		/* avoid atomic ops if this isn't a client */
		if (sta_priv->client &&
		    atomic_dec_return(&sta_priv->pending_frames) == 0)
			ieee80211_sta_block_awake(il->hw, sta, false);
	}
	rcu_read_unlock();
}