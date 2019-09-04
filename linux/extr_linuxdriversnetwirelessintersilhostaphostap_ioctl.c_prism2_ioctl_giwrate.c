#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int fixed; int value; } ;
struct hostap_interface {TYPE_3__* local; } ;
struct TYPE_6__ {scalar_t__ iw_mode; TYPE_2__* func; TYPE_1__* ap; int /*<<< orphan*/  fw_tx_rate_control; } ;
typedef  TYPE_3__ local_info_t ;
struct TYPE_5__ {scalar_t__ (* get_rid ) (struct net_device*,int /*<<< orphan*/ ,int*,int,int) ;} ;
struct TYPE_4__ {int last_tx_rate; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HFA384X_RATES_11MBPS 131 
#define  HFA384X_RATES_1MBPS 130 
#define  HFA384X_RATES_2MBPS 129 
#define  HFA384X_RATES_5MBPS 128 
 int /*<<< orphan*/  HFA384X_RID_CURRENTTXRATE ; 
 int /*<<< orphan*/  HFA384X_RID_TXRATECONTROL ; 
 scalar_t__ IW_MODE_MASTER ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,int*,int,int) ; 
 scalar_t__ stub2 (struct net_device*,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int prism2_ioctl_giwrate(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_param *rrq, char *extra)
{
	u16 val;
	struct hostap_interface *iface;
	local_info_t *local;
	int ret = 0;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->func->get_rid(dev, HFA384X_RID_TXRATECONTROL, &val, 2, 1) <
	    0)
		return -EINVAL;

	if ((val & 0x1) && (val > 1))
		rrq->fixed = 0;
	else
		rrq->fixed = 1;

	if (local->iw_mode == IW_MODE_MASTER && local->ap != NULL &&
	    !local->fw_tx_rate_control) {
		/* HFA384X_RID_CURRENTTXRATE seems to always be 2 Mbps in
		 * Host AP mode, so use the recorded TX rate of the last sent
		 * frame */
		rrq->value = local->ap->last_tx_rate > 0 ?
			local->ap->last_tx_rate * 100000 : 11000000;
		return 0;
	}

	if (local->func->get_rid(dev, HFA384X_RID_CURRENTTXRATE, &val, 2, 1) <
	    0)
		return -EINVAL;

	switch (val) {
	case HFA384X_RATES_1MBPS:
		rrq->value = 1000000;
		break;
	case HFA384X_RATES_2MBPS:
		rrq->value = 2000000;
		break;
	case HFA384X_RATES_5MBPS:
		rrq->value = 5500000;
		break;
	case HFA384X_RATES_11MBPS:
		rrq->value = 11000000;
		break;
	default:
		/* should not happen */
		rrq->value = 11000000;
		ret = -EINVAL;
		break;
	}

	return ret;
}