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
struct ieee80211_low_level_stats {int /*<<< orphan*/  dot11FCSErrorCount; int /*<<< orphan*/  dot11RTSSuccessCount; int /*<<< orphan*/  dot11RTSFailureCount; int /*<<< orphan*/  dot11ACKFailureCount; } ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  fcs_error; int /*<<< orphan*/  rts_ok; int /*<<< orphan*/  rts_fail; int /*<<< orphan*/  ack_fail; } ;
struct ath5k_hw {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_hw_update_mib_counters (struct ath5k_hw*) ; 

__attribute__((used)) static int
ath5k_get_stats(struct ieee80211_hw *hw,
		struct ieee80211_low_level_stats *stats)
{
	struct ath5k_hw *ah = hw->priv;

	/* Force update */
	ath5k_hw_update_mib_counters(ah);

	stats->dot11ACKFailureCount = ah->stats.ack_fail;
	stats->dot11RTSFailureCount = ah->stats.rts_fail;
	stats->dot11RTSSuccessCount = ah->stats.rts_ok;
	stats->dot11FCSErrorCount = ah->stats.fcs_error;

	return 0;
}