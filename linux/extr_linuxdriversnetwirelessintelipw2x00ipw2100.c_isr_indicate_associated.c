#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  int u32 ;
struct ipw2100_priv {int config; int essid_len; int channel; int /*<<< orphan*/  wx_event_work; int /*<<< orphan*/  connect_start; int /*<<< orphan*/  status; int /*<<< orphan*/  bssid; int /*<<< orphan*/  essid; TYPE_2__* net_dev; TYPE_1__* ieee; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int CFG_STATIC_ESSID ; 
 int ETH_ALEN ; 
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int,...) ; 
 int /*<<< orphan*/  IPW_ORD_CURRENT_TX_RATE ; 
 int /*<<< orphan*/  IPW_ORD_OUR_FREQ ; 
 int /*<<< orphan*/  IPW_ORD_STAT_ASSN_AP_BSSID ; 
 int /*<<< orphan*/  IPW_ORD_STAT_ASSN_SSID ; 
 int IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  STATUS_ASSOCIATING ; 
#define  TX_RATE_11_MBIT 131 
#define  TX_RATE_1_MBIT 130 
#define  TX_RATE_2_MBIT 129 
#define  TX_RATE_5_5_MBIT 128 
 int ipw2100_get_ordinal (struct ipw2100_priv*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ktime_get_boottime_seconds () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int min (char,char) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void isr_indicate_associated(struct ipw2100_priv *priv, u32 status)
{

#define MAC_ASSOCIATION_READ_DELAY (HZ)
	int ret;
	unsigned int len, essid_len;
	char essid[IW_ESSID_MAX_SIZE];
	u32 txrate;
	u32 chan;
	char *txratename;
	u8 bssid[ETH_ALEN];

	/*
	 * TBD: BSSID is usually 00:00:00:00:00:00 here and not
	 *      an actual MAC of the AP. Seems like FW sets this
	 *      address too late. Read it later and expose through
	 *      /proc or schedule a later task to query and update
	 */

	essid_len = IW_ESSID_MAX_SIZE;
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_SSID,
				  essid, &essid_len);
	if (ret) {
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		return;
	}

	len = sizeof(u32);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_CURRENT_TX_RATE, &txrate, &len);
	if (ret) {
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		return;
	}

	len = sizeof(u32);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_OUR_FREQ, &chan, &len);
	if (ret) {
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		return;
	}
	len = ETH_ALEN;
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_AP_BSSID, bssid,
				  &len);
	if (ret) {
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		return;
	}
	memcpy(priv->ieee->bssid, bssid, ETH_ALEN);

	switch (txrate) {
	case TX_RATE_1_MBIT:
		txratename = "1Mbps";
		break;
	case TX_RATE_2_MBIT:
		txratename = "2Mbsp";
		break;
	case TX_RATE_5_5_MBIT:
		txratename = "5.5Mbps";
		break;
	case TX_RATE_11_MBIT:
		txratename = "11Mbps";
		break;
	default:
		IPW_DEBUG_INFO("Unknown rate: %d\n", txrate);
		txratename = "unknown rate";
		break;
	}

	IPW_DEBUG_INFO("%s: Associated with '%*pE' at %s, channel %d (BSSID=%pM)\n",
		       priv->net_dev->name, essid_len, essid,
		       txratename, chan, bssid);

	/* now we copy read ssid into dev */
	if (!(priv->config & CFG_STATIC_ESSID)) {
		priv->essid_len = min((u8) essid_len, (u8) IW_ESSID_MAX_SIZE);
		memcpy(priv->essid, essid, priv->essid_len);
	}
	priv->channel = chan;
	memcpy(priv->bssid, bssid, ETH_ALEN);

	priv->status |= STATUS_ASSOCIATING;
	priv->connect_start = ktime_get_boottime_seconds();

	schedule_delayed_work(&priv->wx_event_work, HZ / 10);
}