#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rssi; } ;
struct libipw_network {int capability; scalar_t__ ssid_len; scalar_t__ last_associate; scalar_t__ last_scanned; scalar_t__ channel; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; int /*<<< orphan*/  mode; TYPE_1__ stats; } ;
struct ipw_supported_rates {scalar_t__ num_rates; } ;
struct ipw_priv {int config; scalar_t__ essid_len; scalar_t__ channel; int capability; TYPE_2__* ieee; int /*<<< orphan*/  bssid; int /*<<< orphan*/  essid; } ;
struct ipw_network_match {struct libipw_network* network; int /*<<< orphan*/  rates; } ;
struct TYPE_5__ {scalar_t__ iw_mode; scalar_t__ scan_age; } ;

/* Variables and functions */
 int CAP_PRIVACY_ON ; 
 int CFG_STATIC_BSSID ; 
 int CFG_STATIC_CHANNEL ; 
 int CFG_STATIC_ESSID ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_ASSOC (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int WLAN_CAPABILITY_ESS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_compatible_rates (struct ipw_priv*,struct libipw_network*,struct ipw_supported_rates*) ; 
 int /*<<< orphan*/  ipw_copy_rates (int /*<<< orphan*/ *,struct ipw_supported_rates*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  libipw_is_valid_channel (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  libipw_is_valid_mode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipw_best_network(struct ipw_priv *priv,
			    struct ipw_network_match *match,
			    struct libipw_network *network, int roaming)
{
	struct ipw_supported_rates rates;

	/* Verify that this network's capability is compatible with the
	 * current mode (AdHoc or Infrastructure) */
	if ((priv->ieee->iw_mode == IW_MODE_INFRA &&
	     !(network->capability & WLAN_CAPABILITY_ESS)) ||
	    (priv->ieee->iw_mode == IW_MODE_ADHOC &&
	     !(network->capability & WLAN_CAPABILITY_IBSS))) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded due to capability mismatch.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		return 0;
	}

	if (unlikely(roaming)) {
		/* If we are roaming, then ensure check if this is a valid
		 * network to try and roam to */
		if ((network->ssid_len != match->network->ssid_len) ||
		    memcmp(network->ssid, match->network->ssid,
			   network->ssid_len)) {
			IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of non-network ESSID.\n",
					network->ssid_len, network->ssid,
					network->bssid);
			return 0;
		}
	} else {
		/* If an ESSID has been configured then compare the broadcast
		 * ESSID to ours */
		if ((priv->config & CFG_STATIC_ESSID) &&
		    ((network->ssid_len != priv->essid_len) ||
		     memcmp(network->ssid, priv->essid,
			    min(network->ssid_len, priv->essid_len)))) {
			IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of ESSID mismatch: '%*pE'.\n",
					network->ssid_len, network->ssid,
					network->bssid, priv->essid_len,
					priv->essid);
			return 0;
		}
	}

	/* If the old network rate is better than this one, don't bother
	 * testing everything else. */
	if (match->network && match->network->stats.rssi > network->stats.rssi) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because '%*pE (%pM)' has a stronger signal.\n",
				network->ssid_len, network->ssid,
				network->bssid, match->network->ssid_len,
				match->network->ssid, match->network->bssid);
		return 0;
	}

	/* If this network has already had an association attempt within the
	 * last 3 seconds, do not try and associate again... */
	if (network->last_associate &&
	    time_after(network->last_associate + (HZ * 3UL), jiffies)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of storming (%ums since last assoc attempt).\n",
				network->ssid_len, network->ssid,
				network->bssid,
				jiffies_to_msecs(jiffies -
						 network->last_associate));
		return 0;
	}

	/* Now go through and see if the requested network is valid... */
	if (priv->ieee->scan_age != 0 &&
	    time_after(jiffies, network->last_scanned + priv->ieee->scan_age)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of age: %ums.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				jiffies_to_msecs(jiffies -
						 network->last_scanned));
		return 0;
	}

	if ((priv->config & CFG_STATIC_CHANNEL) &&
	    (network->channel != priv->channel)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of channel mismatch: %d != %d.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				network->channel, priv->channel);
		return 0;
	}

	/* Verify privacy compatibility */
	if (((priv->capability & CAP_PRIVACY_ON) ? 1 : 0) !=
	    ((network->capability & WLAN_CAPABILITY_PRIVACY) ? 1 : 0)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of privacy mismatch: %s != %s.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				priv->capability & CAP_PRIVACY_ON ? "on" :
				"off",
				network->capability &
				WLAN_CAPABILITY_PRIVACY ? "on" : "off");
		return 0;
	}

	if ((priv->config & CFG_STATIC_BSSID) &&
	    !ether_addr_equal(network->bssid, priv->bssid)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of BSSID mismatch: %pM.\n",
				network->ssid_len, network->ssid,
				network->bssid, priv->bssid);
		return 0;
	}

	/* Filter out any incompatible freq / mode combinations */
	if (!libipw_is_valid_mode(priv->ieee, network->mode)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of invalid frequency/mode combination.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		return 0;
	}

	/* Filter out invalid channel in current GEO */
	if (!libipw_is_valid_channel(priv->ieee, network->channel)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of invalid channel in current GEO\n",
				network->ssid_len, network->ssid,
				network->bssid);
		return 0;
	}

	/* Ensure that the rates supported by the driver are compatible with
	 * this AP, including verification of basic rates (mandatory) */
	if (!ipw_compatible_rates(priv, network, &rates)) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because configured rate mask excludes AP mandatory rate.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		return 0;
	}

	if (rates.num_rates == 0) {
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of no compatible rates.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		return 0;
	}

	/* TODO: Perform any further minimal comparititive tests.  We do not
	 * want to put too much policy logic here; intelligent scan selection
	 * should occur within a generic IEEE 802.11 user space tool.  */

	/* Set up 'new' AP to this network */
	ipw_copy_rates(&match->rates, &rates);
	match->network = network;

	IPW_DEBUG_ASSOC("Network '%*pE (%pM)' is a viable match.\n",
			network->ssid_len, network->ssid, network->bssid);

	return 1;
}