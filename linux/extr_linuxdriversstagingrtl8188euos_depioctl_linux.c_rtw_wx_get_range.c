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
struct TYPE_6__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct mlme_ext_priv {TYPE_4__* channel_set; } ;
struct iw_request_info {int /*<<< orphan*/  cmd; } ;
struct TYPE_8__ {int qual; int level; int updated; scalar_t__ noise; } ;
struct TYPE_7__ {int qual; int level; int noise; int updated; } ;
struct iw_range {int throughput; int num_bitrates; int we_version_source; size_t num_channels; size_t num_frequency; int enc_capa; int scan_capa; TYPE_5__* freq; int /*<<< orphan*/  we_version_compiled; scalar_t__ pm_capa; int /*<<< orphan*/  max_frag; int /*<<< orphan*/  min_frag; int /*<<< orphan*/ * bitrate; TYPE_3__ avg_qual; TYPE_2__ max_qual; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_10__ {scalar_t__ i; int m; int e; } ;
struct TYPE_9__ {scalar_t__ ChannelNum; } ;

/* Variables and functions */
 int IW_ENC_CAPA_CIPHER_CCMP ; 
 int IW_ENC_CAPA_CIPHER_TKIP ; 
 int IW_ENC_CAPA_WPA ; 
 int IW_ENC_CAPA_WPA2 ; 
 int IW_MAX_BITRATES ; 
 size_t IW_MAX_FREQUENCIES ; 
 int IW_SCAN_CAPA_BSSID ; 
 int IW_SCAN_CAPA_CHANNEL ; 
 int IW_SCAN_CAPA_ESSID ; 
 int IW_SCAN_CAPA_MODE ; 
 int IW_SCAN_CAPA_RATE ; 
 int IW_SCAN_CAPA_TYPE ; 
 int MAX_CHANNEL_NUM ; 
 int /*<<< orphan*/  MAX_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  MIN_FRAG_THRESHOLD ; 
 int RATE_COUNT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIRELESS_EXT ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 
 int rtw_ch2freq (scalar_t__) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/ * rtw_rates ; 

__attribute__((used)) static int rtw_wx_get_range(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct iw_range *range = (struct iw_range *)extra;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;

	u16 val;
	int i;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_wx_get_range. cmd_code =%x\n", info->cmd));

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

	/* signal level threshold range */

	/* percent values between 0 and 100. */
	range->max_qual.qual = 100;
	range->max_qual.level = 100;
	range->max_qual.noise = 100;
	range->max_qual.updated = 7; /* Updated all three */

	range->avg_qual.qual = 92; /* > 8% missed beacons is 'bad' */
	/* TODO: Find real 'good' to 'bad' threshol value for RSSI */
	range->avg_qual.level = 178; /* -78 dBm */
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7; /* Updated all three */

	range->num_bitrates = RATE_COUNT;

	for (i = 0; i < RATE_COUNT && i < IW_MAX_BITRATES; i++)
		range->bitrate[i] = rtw_rates[i];

	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;

	range->pm_capa = 0;

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 16;

	for (i = 0, val = 0; i < MAX_CHANNEL_NUM; i++) {
		/*  Include only legal frequencies for some countries */
		if (pmlmeext->channel_set[i].ChannelNum != 0) {
			range->freq[val].i = pmlmeext->channel_set[i].ChannelNum;
			range->freq[val].m = rtw_ch2freq(pmlmeext->channel_set[i].ChannelNum) * 100000;
			range->freq[val].e = 1;
			val++;
		}

		if (val == IW_MAX_FREQUENCIES)
			break;
	}

	range->num_channels = val;
	range->num_frequency = val;

/*  The following code will proivde the security capability to network manager. */
/*  If the driver doesn't provide this capability to network manager, */
/*  the WPA/WPA2 routers can't be chosen in the network manager. */

/*
#define IW_SCAN_CAPA_NONE		0x00
#define IW_SCAN_CAPA_ESSID		0x01
#define IW_SCAN_CAPA_BSSID		0x02
#define IW_SCAN_CAPA_CHANNEL		0x04
#define IW_SCAN_CAPA_MODE		0x08
#define IW_SCAN_CAPA_RATE		0x10
#define IW_SCAN_CAPA_TYPE		0x20
#define IW_SCAN_CAPA_TIME		0x40
*/

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	range->scan_capa = IW_SCAN_CAPA_ESSID | IW_SCAN_CAPA_TYPE |
			   IW_SCAN_CAPA_BSSID | IW_SCAN_CAPA_CHANNEL |
			   IW_SCAN_CAPA_MODE | IW_SCAN_CAPA_RATE;
	return 0;
}