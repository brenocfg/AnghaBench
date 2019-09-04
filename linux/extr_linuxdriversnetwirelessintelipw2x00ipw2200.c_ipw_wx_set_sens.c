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
struct TYPE_2__ {int value; scalar_t__ fixed; } ;
union iwreq_data {TYPE_1__ sens; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int roaming_threshold; int disassociate_threshold; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int) ; 
 int IPW_MB_DISASSOCIATE_THRESHOLD_DEFAULT ; 
 int IPW_MB_ROAMING_THRESHOLD_DEFAULT ; 
 int IPW_MB_ROAMING_THRESHOLD_MAX ; 
 int IPW_MB_ROAMING_THRESHOLD_MIN ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_sens(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	int err = 0;

	IPW_DEBUG_WX("Setting roaming threshold to %d\n", wrqu->sens.value);
	IPW_DEBUG_WX("Setting disassociate threshold to %d\n", 3*wrqu->sens.value);
	mutex_lock(&priv->mutex);

	if (wrqu->sens.fixed == 0)
	{
		priv->roaming_threshold = IPW_MB_ROAMING_THRESHOLD_DEFAULT;
		priv->disassociate_threshold = IPW_MB_DISASSOCIATE_THRESHOLD_DEFAULT;
		goto out;
	}
	if ((wrqu->sens.value > IPW_MB_ROAMING_THRESHOLD_MAX) ||
	    (wrqu->sens.value < IPW_MB_ROAMING_THRESHOLD_MIN)) {
		err = -EINVAL;
		goto out;
	}

	priv->roaming_threshold = wrqu->sens.value;
	priv->disassociate_threshold = 3*wrqu->sens.value;
      out:
	mutex_unlock(&priv->mutex);
	return err;
}