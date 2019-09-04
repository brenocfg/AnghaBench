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
struct ath_common {int dummy; } ;
struct TYPE_2__ {int beaconq; } ;
struct ath9k_htc_priv {int* hwq_map; int cabq; TYPE_1__ beacon; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_AC_BE ; 
 int /*<<< orphan*/  IEEE80211_AC_BK ; 
 int /*<<< orphan*/  IEEE80211_AC_VI ; 
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 int ath9k_htc_cabq_setup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_txq_setup (struct ath9k_htc_priv*,int /*<<< orphan*/ ) ; 
 int ath9k_hw_beaconq_setup (int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 

__attribute__((used)) static int ath9k_init_queues(struct ath9k_htc_priv *priv)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	int i;

	for (i = 0; i < ARRAY_SIZE(priv->hwq_map); i++)
		priv->hwq_map[i] = -1;

	priv->beacon.beaconq = ath9k_hw_beaconq_setup(priv->ah);
	if (priv->beacon.beaconq == -1) {
		ath_err(common, "Unable to setup BEACON xmit queue\n");
		goto err;
	}

	priv->cabq = ath9k_htc_cabq_setup(priv);
	if (priv->cabq == -1) {
		ath_err(common, "Unable to setup CAB xmit queue\n");
		goto err;
	}

	if (!ath9k_htc_txq_setup(priv, IEEE80211_AC_BE)) {
		ath_err(common, "Unable to setup xmit queue for BE traffic\n");
		goto err;
	}

	if (!ath9k_htc_txq_setup(priv, IEEE80211_AC_BK)) {
		ath_err(common, "Unable to setup xmit queue for BK traffic\n");
		goto err;
	}
	if (!ath9k_htc_txq_setup(priv, IEEE80211_AC_VI)) {
		ath_err(common, "Unable to setup xmit queue for VI traffic\n");
		goto err;
	}
	if (!ath9k_htc_txq_setup(priv, IEEE80211_AC_VO)) {
		ath_err(common, "Unable to setup xmit queue for VO traffic\n");
		goto err;
	}

	return 0;

err:
	return -EINVAL;
}