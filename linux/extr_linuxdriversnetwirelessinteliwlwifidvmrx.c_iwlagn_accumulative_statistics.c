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
struct statistics_tx {int dummy; } ;
struct statistics_rx_phy {int dummy; } ;
struct statistics_rx_non_phy {int dummy; } ;
struct statistics_rx_ht_phy {int dummy; } ;
struct statistics_general_common {int dummy; } ;
struct statistics_bt_activity {int dummy; } ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
iwlagn_accumulative_statistics(struct iwl_priv *priv,
			    struct statistics_general_common *common,
			    struct statistics_rx_non_phy *rx_non_phy,
			    struct statistics_rx_phy *rx_ofdm,
			    struct statistics_rx_ht_phy *rx_ofdm_ht,
			    struct statistics_rx_phy *rx_cck,
			    struct statistics_tx *tx,
			    struct statistics_bt_activity *bt_activity)
{
}