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
struct TYPE_3__ {int /*<<< orphan*/  value; scalar_t__ disabled; } ;
struct TYPE_4__ {int fixed; int /*<<< orphan*/  value; } ;
union iwreq_data {TYPE_1__ power; TYPE_2__ sens; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  roaming_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,char*,int /*<<< orphan*/ ) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_get_sens(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->sens.fixed = 1;
	wrqu->sens.value = priv->roaming_threshold;
	mutex_unlock(&priv->mutex);

	IPW_DEBUG_WX("GET roaming threshold -> %s %d\n",
		     wrqu->power.disabled ? "OFF" : "ON", wrqu->power.value);

	return 0;
}