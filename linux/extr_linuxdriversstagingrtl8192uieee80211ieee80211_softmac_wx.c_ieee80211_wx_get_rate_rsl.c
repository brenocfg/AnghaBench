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
struct TYPE_4__ {int value; } ;
union iwreq_data {TYPE_2__ bitrate; } ;
typedef  int u32 ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  CurrentShowTxate; } ;
struct ieee80211_device {TYPE_1__ softmac_stats; } ;

/* Variables and functions */
 int TxCountToDataRate (struct ieee80211_device*,int /*<<< orphan*/ ) ; 

int ieee80211_wx_get_rate(struct ieee80211_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	u32 tmp_rate;

	tmp_rate = TxCountToDataRate(ieee, ieee->softmac_stats.CurrentShowTxate);

	wrqu->bitrate.value = tmp_rate * 500000;

	return 0;
}