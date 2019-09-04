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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_MULTI_CHANNEL ; 
 int /*<<< orphan*/  __ath9k_flush (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 scalar_t__ ath9k_is_chanctx_enabled () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_flush(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			u32 queues, bool drop)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (ath9k_is_chanctx_enabled()) {
		if (!test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags))
			goto flush;

		/*
		 * If MCC is active, extend the flush timeout
		 * and wait for the HW/SW queues to become
		 * empty. This needs to be done outside the
		 * sc->mutex lock to allow the channel scheduler
		 * to switch channel contexts.
		 *
		 * The vif queues have been stopped in mac80211,
		 * so there won't be any incoming frames.
		 */
		__ath9k_flush(hw, queues, drop, true, true);
		return;
	}
flush:
	mutex_lock(&sc->mutex);
	__ath9k_flush(hw, queues, drop, true, false);
	mutex_unlock(&sc->mutex);
}