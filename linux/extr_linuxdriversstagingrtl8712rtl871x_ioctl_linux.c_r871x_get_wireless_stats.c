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
struct net_device {int dummy; } ;
struct TYPE_4__ {int qual; int level; int noise; int /*<<< orphan*/  updated; } ;
struct iw_statistics {TYPE_2__ qual; } ;
struct TYPE_3__ {int fw_rssi; int signal; int noise; } ;
struct _adapter {struct iw_statistics iwstats; TYPE_1__ recvpriv; int /*<<< orphan*/  mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_QUAL_ALL_UPDATED ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct iw_statistics *r871x_get_wireless_stats(struct net_device *dev)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct iw_statistics *piwstats = &padapter->iwstats;
	int tmp_level = 0;
	int tmp_qual = 0;
	int tmp_noise = 0;

	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED) != true) {
		piwstats->qual.qual = 0;
		piwstats->qual.level = 0;
		piwstats->qual.noise = 0;
	} else {
		/* show percentage, we need transfer dbm to original value. */
		tmp_level = padapter->recvpriv.fw_rssi;
		tmp_qual = padapter->recvpriv.signal;
		tmp_noise = padapter->recvpriv.noise;
		piwstats->qual.level = tmp_level;
		piwstats->qual.qual = tmp_qual;
		piwstats->qual.noise = tmp_noise;
	}
	piwstats->qual.updated = IW_QUAL_ALL_UPDATED;
	return &padapter->iwstats;
}