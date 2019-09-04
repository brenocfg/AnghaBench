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
struct cfg80211_chan_def {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  chan_lock; struct ath_chanctx* cur_chan; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
struct ath_chanctx {int /*<<< orphan*/  chandef; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_CTX ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_set_channel (struct ath_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath_chanctx_set_channel(struct ath_softc *sc, struct ath_chanctx *ctx,
			     struct cfg80211_chan_def *chandef)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	bool cur_chan;

	spin_lock_bh(&sc->chan_lock);
	if (chandef)
		memcpy(&ctx->chandef, chandef, sizeof(*chandef));
	cur_chan = sc->cur_chan == ctx;
	spin_unlock_bh(&sc->chan_lock);

	if (!cur_chan) {
		ath_dbg(common, CHAN_CTX,
			"Current context differs from the new context\n");
		return;
	}

	ath_set_channel(sc);
}