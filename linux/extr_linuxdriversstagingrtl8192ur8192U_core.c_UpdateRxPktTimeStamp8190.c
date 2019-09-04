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
struct r8192_priv {int /*<<< orphan*/  LastRxDescTSFHigh; int /*<<< orphan*/  LastRxDescTSFLow; } ;
struct net_device {int dummy; } ;
struct ieee80211_rx_stats {int /*<<< orphan*/ * mac_time; int /*<<< orphan*/  bFirstMPDU; scalar_t__ bIsAMPDU; } ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void UpdateRxPktTimeStamp8190(struct net_device *dev,
				     struct ieee80211_rx_stats *stats)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);

	if (stats->bIsAMPDU && !stats->bFirstMPDU) {
		stats->mac_time[0] = priv->LastRxDescTSFLow;
		stats->mac_time[1] = priv->LastRxDescTSFHigh;
	} else {
		priv->LastRxDescTSFLow = stats->mac_time[0];
		priv->LastRxDescTSFHigh = stats->mac_time[1];
	}
}