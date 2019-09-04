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
struct TYPE_2__ {int m; int e; } ;
union iwreq_data {TYPE_1__ freq; } ;
struct wl3501_card {int /*<<< orphan*/  chan; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int wl3501_get_freq(struct net_device *dev, struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct wl3501_card *this = netdev_priv(dev);

	wrqu->freq.m = 100000 *
		ieee80211_channel_to_frequency(this->chan, NL80211_BAND_2GHZ);
	wrqu->freq.e = 1;
	return 0;
}