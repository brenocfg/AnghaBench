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
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_target_rate {int /*<<< orphan*/  capflags; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int ath9k_htc_send_rate_cmd (struct ath9k_htc_priv*,struct ath9k_htc_target_rate*) ; 
 int /*<<< orphan*/  ath9k_htc_setup_rate (struct ath9k_htc_priv*,struct ieee80211_sta*,struct ath9k_htc_target_rate*) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ath9k_htc_target_rate*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath9k_htc_init_rate(struct ath9k_htc_priv *priv,
				struct ieee80211_sta *sta)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_target_rate trate;
	int ret;

	memset(&trate, 0, sizeof(struct ath9k_htc_target_rate));
	ath9k_htc_setup_rate(priv, sta, &trate);
	ret = ath9k_htc_send_rate_cmd(priv, &trate);
	if (!ret)
		ath_dbg(common, CONFIG,
			"Updated target sta: %pM, rate caps: 0x%X\n",
			sta->addr, be32_to_cpu(trate.capflags));
}