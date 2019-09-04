#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  code; scalar_t__ retries; } ;
struct TYPE_7__ {scalar_t__ beacon; } ;
struct TYPE_6__ {int updated; scalar_t__ noise; scalar_t__ level; scalar_t__ qual; } ;
struct iw_statistics {TYPE_3__ discard; TYPE_2__ miss; TYPE_1__ qual; } ;
struct ipw_priv {int status; TYPE_5__* ieee; scalar_t__ last_tx_failures; int /*<<< orphan*/  average_missed_beacons; scalar_t__ exp_avg_noise; scalar_t__ exp_avg_rssi; scalar_t__ quality; struct iw_statistics wstats; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_discards_undecryptable; } ;
struct TYPE_10__ {TYPE_4__ ieee_stats; } ;

/* Variables and functions */
 int IW_QUAL_DBM ; 
 int IW_QUAL_LEVEL_INVALID ; 
 int IW_QUAL_LEVEL_UPDATED ; 
 int IW_QUAL_NOISE_INVALID ; 
 int IW_QUAL_NOISE_UPDATED ; 
 int IW_QUAL_QUAL_INVALID ; 
 int IW_QUAL_QUAL_UPDATED ; 
 int STATUS_ASSOCIATED ; 
 scalar_t__ average_value (int /*<<< orphan*/ *) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static struct iw_statistics *ipw_get_wireless_stats(struct net_device *dev)
{
	struct ipw_priv *priv = libipw_priv(dev);
	struct iw_statistics *wstats;

	wstats = &priv->wstats;

	/* if hw is disabled, then ipw_get_ordinal() can't be called.
	 * netdev->get_wireless_stats seems to be called before fw is
	 * initialized.  STATUS_ASSOCIATED will only be set if the hw is up
	 * and associated; if not associcated, the values are all meaningless
	 * anyway, so set them all to NULL and INVALID */
	if (!(priv->status & STATUS_ASSOCIATED)) {
		wstats->miss.beacon = 0;
		wstats->discard.retries = 0;
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
		wstats->qual.noise = 0;
		wstats->qual.updated = 7;
		wstats->qual.updated |= IW_QUAL_NOISE_INVALID |
		    IW_QUAL_QUAL_INVALID | IW_QUAL_LEVEL_INVALID;
		return wstats;
	}

	wstats->qual.qual = priv->quality;
	wstats->qual.level = priv->exp_avg_rssi;
	wstats->qual.noise = priv->exp_avg_noise;
	wstats->qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED |
	    IW_QUAL_NOISE_UPDATED | IW_QUAL_DBM;

	wstats->miss.beacon = average_value(&priv->average_missed_beacons);
	wstats->discard.retries = priv->last_tx_failures;
	wstats->discard.code = priv->ieee->ieee_stats.rx_discards_undecryptable;

/*	if (ipw_get_ordinal(priv, IPW_ORD_STAT_TX_RETRY, &tx_retry, &len))
	goto fail_get_ordinal;
	wstats->discard.retries += tx_retry; */

	return wstats;
}