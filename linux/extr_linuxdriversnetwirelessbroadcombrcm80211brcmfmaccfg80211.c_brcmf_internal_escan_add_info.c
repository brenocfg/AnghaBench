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
typedef  scalar_t__ u8 ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_scan_request {int n_channels; int n_ssids; TYPE_1__* ssids; struct ieee80211_channel** channels; int /*<<< orphan*/  wiphy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 scalar_t__ CH_MAX_2G_CHANNEL ; 
 int EINVAL ; 
 int NL80211_BAND_2GHZ ; 
 int NL80211_BAND_5GHZ ; 
 int ieee80211_channel_to_frequency (scalar_t__,int) ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int brcmf_internal_escan_add_info(struct cfg80211_scan_request *req,
					 u8 *ssid, u8 ssid_len, u8 channel)
{
	struct ieee80211_channel *chan;
	enum nl80211_band band;
	int freq, i;

	if (channel <= CH_MAX_2G_CHANNEL)
		band = NL80211_BAND_2GHZ;
	else
		band = NL80211_BAND_5GHZ;

	freq = ieee80211_channel_to_frequency(channel, band);
	if (!freq)
		return -EINVAL;

	chan = ieee80211_get_channel(req->wiphy, freq);
	if (!chan)
		return -EINVAL;

	for (i = 0; i < req->n_channels; i++) {
		if (req->channels[i] == chan)
			break;
	}
	if (i == req->n_channels)
		req->channels[req->n_channels++] = chan;

	for (i = 0; i < req->n_ssids; i++) {
		if (req->ssids[i].ssid_len == ssid_len &&
		    !memcmp(req->ssids[i].ssid, ssid, ssid_len))
			break;
	}
	if (i == req->n_ssids) {
		memcpy(req->ssids[req->n_ssids].ssid, ssid, ssid_len);
		req->ssids[req->n_ssids++].ssid_len = ssid_len;
	}
	return 0;
}