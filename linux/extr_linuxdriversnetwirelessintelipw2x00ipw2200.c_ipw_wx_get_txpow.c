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
struct TYPE_2__ {int fixed; int disabled; int /*<<< orphan*/  value; int /*<<< orphan*/  flags; } ;
union iwreq_data {TYPE_1__ power; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int status; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tx_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IW_TXPOW_DBM ; 
 int STATUS_RF_KILL_MASK ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_get_txpow(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->power.value = priv->tx_power;
	wrqu->power.fixed = 1;
	wrqu->power.flags = IW_TXPOW_DBM;
	wrqu->power.disabled = (priv->status & STATUS_RF_KILL_MASK) ? 1 : 0;
	mutex_unlock(&priv->mutex);

	IPW_DEBUG_WX("GET TX Power -> %s %d\n",
		     wrqu->power.disabled ? "OFF" : "ON", wrqu->power.value);

	return 0;
}