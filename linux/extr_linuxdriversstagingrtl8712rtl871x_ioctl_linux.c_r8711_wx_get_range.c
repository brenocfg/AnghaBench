#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_7__ {int qual; int level; int updated; scalar_t__ noise; } ;
struct TYPE_6__ {int qual; int level; int noise; int updated; } ;
struct iw_range {int throughput; int num_bitrates; int we_version_source; int num_channels; size_t num_frequency; int enc_capa; TYPE_4__* freq; int /*<<< orphan*/  we_version_compiled; scalar_t__ pm_capa; int /*<<< orphan*/  max_frag; int /*<<< orphan*/  min_frag; int /*<<< orphan*/ * bitrate; TYPE_3__ avg_qual; TYPE_2__ max_qual; } ;
struct TYPE_8__ {int i; int m; int e; } ;

/* Variables and functions */
 int IW_ENC_CAPA_CIPHER_CCMP ; 
 int IW_ENC_CAPA_CIPHER_TKIP ; 
 int IW_ENC_CAPA_WPA ; 
 int IW_ENC_CAPA_WPA2 ; 
 int IW_MAX_BITRATES ; 
 size_t IW_MAX_FREQUENCIES ; 
 int /*<<< orphan*/  MAX_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  MIN_FRAG_THRESHOLD ; 
 int RATE_COUNT ; 
 int /*<<< orphan*/  WIRELESS_EXT ; 
 int* ieee80211_wlan_frequencies ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * rtl8180_rates ; 

__attribute__((used)) static int r8711_wx_get_range(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct iw_range *range = (struct iw_range *)extra;
	u16 val;
	int i;

	wrqu->data.length = sizeof(*range);
	memset(range, 0, sizeof(*range));
	/* Let's try to keep this struct in the same order as in
	 * linux/include/wireless.h
	 */

	/* TODO: See what values we can set, and remove the ones we can't
	 * set, or fill them with some default data.
	 */
	/* ~5 Mb/s real (802.11b) */
	range->throughput = 5 * 1000 * 1000;
	/* TODO: 8711 sensitivity ? */
	/* signal level threshold range */
	/* percent values between 0 and 100. */
	range->max_qual.qual = 100;
	range->max_qual.level = 100;
	range->max_qual.noise = 100;
	range->max_qual.updated = 7; /* Updated all three */
	range->avg_qual.qual = 92; /* > 8% missed beacons is 'bad' */
	/* TODO: Find real 'good' to 'bad' threshold value for RSSI */
	range->avg_qual.level = 0x100 - 78;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7; /* Updated all three */
	range->num_bitrates = RATE_COUNT;
	for (i = 0; i < RATE_COUNT && i < IW_MAX_BITRATES; i++)
		range->bitrate[i] = rtl8180_rates[i];
	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;
	range->pm_capa = 0;
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 16;
	range->num_channels = 14;
	for (i = 0, val = 0; i < 14; i++) {
		/* Include only legal frequencies for some countries */
		range->freq[val].i = i + 1;
		range->freq[val].m = ieee80211_wlan_frequencies[i] * 100000;
		range->freq[val].e = 1;
		val++;
		if (val == IW_MAX_FREQUENCIES)
			break;
	}
	range->num_frequency = val;
	range->enc_capa = IW_ENC_CAPA_WPA |
			  IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHER_TKIP |
			  IW_ENC_CAPA_CIPHER_CCMP;
	return 0;
}