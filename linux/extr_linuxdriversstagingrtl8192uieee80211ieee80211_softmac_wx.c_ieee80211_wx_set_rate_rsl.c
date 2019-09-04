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
struct TYPE_2__ {int value; } ;
union iwreq_data {TYPE_1__ bitrate; } ;
typedef  int u32 ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {int rate; } ;

/* Variables and functions */

int ieee80211_wx_set_rate(struct ieee80211_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{

	u32 target_rate = wrqu->bitrate.value;

	ieee->rate = target_rate/100000;
	/* FIXME: we might want to limit rate also in management protocols. */
	return 0;
}