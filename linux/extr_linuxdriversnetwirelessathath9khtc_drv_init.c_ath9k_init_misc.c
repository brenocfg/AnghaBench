#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_common {int /*<<< orphan*/  last_rssi; int /*<<< orphan*/  bssidmask; } ;
struct TYPE_4__ {int short_repeat; int count; int endless; int period; int fft_period; scalar_t__ enabled; } ;
struct TYPE_5__ {TYPE_1__ spec_config; TYPE_3__* ah; } ;
struct ath9k_htc_priv {TYPE_2__ spec_priv; TYPE_3__* ah; } ;
struct TYPE_6__ {int /*<<< orphan*/  opmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_RSSI_DUMMY_MARKER ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 struct ath_common* ath9k_hw_common (TYPE_3__*) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_init_misc(struct ath9k_htc_priv *priv)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);

	eth_broadcast_addr(common->bssidmask);

	common->last_rssi = ATH_RSSI_DUMMY_MARKER;
	priv->ah->opmode = NL80211_IFTYPE_STATION;

	priv->spec_priv.ah = priv->ah;
	priv->spec_priv.spec_config.enabled = 0;
	priv->spec_priv.spec_config.short_repeat = true;
	priv->spec_priv.spec_config.count = 8;
	priv->spec_priv.spec_config.endless = false;
	priv->spec_priv.spec_config.period = 0x12;
	priv->spec_priv.spec_config.fft_period = 0x02;
}