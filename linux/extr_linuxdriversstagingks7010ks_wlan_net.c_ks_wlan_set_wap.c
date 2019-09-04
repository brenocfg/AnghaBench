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
struct TYPE_3__ {int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ operation_mode; scalar_t__ bssid; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int need_commit; TYPE_2__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ MODE_ADHOC ; 
 scalar_t__ MODE_INFRASTRUCTURE ; 
 scalar_t__ SLP_SLEEP ; 
 int SME_MODE_SET ; 
 int /*<<< orphan*/  eth_zero_addr (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,scalar_t__) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_wap(struct net_device *dev, struct iw_request_info *info,
			   union iwreq_data *awrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	if (priv->reg.operation_mode != MODE_ADHOC &&
	    priv->reg.operation_mode != MODE_INFRASTRUCTURE) {
		eth_zero_addr(priv->reg.bssid);
		return -EOPNOTSUPP;
	}

	ether_addr_copy(priv->reg.bssid, awrq->ap_addr.sa_data);
	if (is_valid_ether_addr((u8 *)priv->reg.bssid))
		priv->need_commit |= SME_MODE_SET;

	netdev_dbg(dev, "bssid = %pM\n", priv->reg.bssid);

	/* Write it to the card */
	if (priv->need_commit) {
		priv->need_commit |= SME_MODE_SET;
		return -EINPROGRESS;	/* Call commit handler */
	}
	return 0;
}