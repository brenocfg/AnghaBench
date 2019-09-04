#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int prism2_ioctl_giwtxpow(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *rrq, char *extra)
{
#ifdef RAW_TXPOWER_SETTING
	struct hostap_interface *iface;
	local_info_t *local;
	u16 resp0;

	iface = netdev_priv(dev);
	local = iface->local;

	rrq->flags = IW_TXPOW_DBM;
	rrq->disabled = 0;
	rrq->fixed = 0;

	if (local->txpower_type == PRISM2_TXPOWER_AUTO) {
		if (local->func->cmd(dev, HFA384X_CMDCODE_READMIF,
				     HFA386X_CR_MANUAL_TX_POWER,
				     NULL, &resp0) == 0) {
			rrq->value = prism2_txpower_hfa386x_to_dBm(resp0);
		} else {
			/* Could not get real txpower; guess 15 dBm */
			rrq->value = 15;
		}
	} else if (local->txpower_type == PRISM2_TXPOWER_OFF) {
		rrq->value = 0;
		rrq->disabled = 1;
	} else if (local->txpower_type == PRISM2_TXPOWER_FIXED) {
		rrq->value = local->txpower;
		rrq->fixed = 1;
	} else {
		printk("SIOCGIWTXPOW - unknown txpower_type=%d\n",
		       local->txpower_type);
	}
	return 0;
#else /* RAW_TXPOWER_SETTING */
	return -EOPNOTSUPP;
#endif /* RAW_TXPOWER_SETTING */
}