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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct rtllib_device {short proto_started; scalar_t__ iw_mode; int wap_set; int cannot_notify; int /*<<< orphan*/  wx_mutex; int /*<<< orphan*/  lock; TYPE_1__ current_network; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EINVAL ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_start_protocol (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_stop_protocol (struct rtllib_device*,int) ; 
 int /*<<< orphan*/  rtllib_stop_scan_syncro (struct rtllib_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int rtllib_wx_set_wap(struct rtllib_device *ieee,
			 struct iw_request_info *info,
			 union iwreq_data *awrq,
			 char *extra)
{

	int ret = 0;
	unsigned long flags;

	short ifup = ieee->proto_started;
	struct sockaddr *temp = (struct sockaddr *)awrq;

	rtllib_stop_scan_syncro(ieee);

	mutex_lock(&ieee->wx_mutex);
	/* use ifconfig hw ether */
	if (ieee->iw_mode == IW_MODE_MASTER) {
		ret = -1;
		goto out;
	}

	if (temp->sa_family != ARPHRD_ETHER) {
		ret = -EINVAL;
		goto out;
	}

	if (is_zero_ether_addr(temp->sa_data)) {
		spin_lock_irqsave(&ieee->lock, flags);
		ether_addr_copy(ieee->current_network.bssid, temp->sa_data);
		ieee->wap_set = 0;
		spin_unlock_irqrestore(&ieee->lock, flags);
		ret = -1;
		goto out;
	}


	if (ifup)
		rtllib_stop_protocol(ieee, true);

	/* just to avoid to give inconsistent infos in the
	 * get wx method. not really needed otherwise
	 */
	spin_lock_irqsave(&ieee->lock, flags);

	ieee->cannot_notify = false;
	ether_addr_copy(ieee->current_network.bssid, temp->sa_data);
	ieee->wap_set = !is_zero_ether_addr(temp->sa_data);

	spin_unlock_irqrestore(&ieee->lock, flags);

	if (ifup)
		rtllib_start_protocol(ieee);
out:
	mutex_unlock(&ieee->wx_mutex);
	return ret;
}