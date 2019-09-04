#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union iwreq_data {int mode; } ;
struct rtllib_device {int iw_mode; int /*<<< orphan*/  wx_mutex; int /*<<< orphan*/  proto_started; TYPE_1__* dev; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
 int EINVAL ; 
#define  IW_MODE_ADHOC 131 
#define  IW_MODE_AUTO 130 
#define  IW_MODE_INFRA 129 
#define  IW_MODE_MONITOR 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_DisableNetMonitorMode (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rtllib_EnableNetMonitorMode (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rtllib_start_protocol (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_stop_protocol (struct rtllib_device*,int) ; 
 int /*<<< orphan*/  rtllib_stop_scan_syncro (struct rtllib_device*) ; 

int rtllib_wx_set_mode(struct rtllib_device *ieee, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	int set_mode_status = 0;

	rtllib_stop_scan_syncro(ieee);
	mutex_lock(&ieee->wx_mutex);
	switch (wrqu->mode) {
	case IW_MODE_MONITOR:
	case IW_MODE_ADHOC:
	case IW_MODE_INFRA:
		break;
	case IW_MODE_AUTO:
		wrqu->mode = IW_MODE_INFRA;
		break;
	default:
		set_mode_status = -EINVAL;
		goto out;
	}

	if (wrqu->mode == ieee->iw_mode)
		goto out;

	if (wrqu->mode == IW_MODE_MONITOR) {
		ieee->dev->type = ARPHRD_IEEE80211;
		rtllib_EnableNetMonitorMode(ieee->dev, false);
	} else {
		ieee->dev->type = ARPHRD_ETHER;
		if (ieee->iw_mode == IW_MODE_MONITOR)
			rtllib_DisableNetMonitorMode(ieee->dev, false);
	}

	if (!ieee->proto_started) {
		ieee->iw_mode = wrqu->mode;
	} else {
		rtllib_stop_protocol(ieee, true);
		ieee->iw_mode = wrqu->mode;
		rtllib_start_protocol(ieee);
	}

out:
	mutex_unlock(&ieee->wx_mutex);
	return set_mode_status;
}