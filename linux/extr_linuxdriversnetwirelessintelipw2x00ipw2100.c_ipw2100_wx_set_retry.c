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
struct TYPE_2__ {int flags; int /*<<< orphan*/  value; scalar_t__ disabled; } ;
union iwreq_data {TYPE_1__ retry; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int /*<<< orphan*/  action_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int /*<<< orphan*/ ) ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int STATUS_INITIALIZED ; 
 int ipw2100_set_long_retry (struct ipw2100_priv*,int /*<<< orphan*/ ) ; 
 int ipw2100_set_short_retry (struct ipw2100_priv*,int /*<<< orphan*/ ) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_retry(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int err = 0;

	if (wrqu->retry.flags & IW_RETRY_LIFETIME || wrqu->retry.disabled)
		return -EINVAL;

	if (!(wrqu->retry.flags & IW_RETRY_LIMIT))
		return 0;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	if (wrqu->retry.flags & IW_RETRY_SHORT) {
		err = ipw2100_set_short_retry(priv, wrqu->retry.value);
		IPW_DEBUG_WX("SET Short Retry Limit -> %d\n",
			     wrqu->retry.value);
		goto done;
	}

	if (wrqu->retry.flags & IW_RETRY_LONG) {
		err = ipw2100_set_long_retry(priv, wrqu->retry.value);
		IPW_DEBUG_WX("SET Long Retry Limit -> %d\n",
			     wrqu->retry.value);
		goto done;
	}

	err = ipw2100_set_short_retry(priv, wrqu->retry.value);
	if (!err)
		err = ipw2100_set_long_retry(priv, wrqu->retry.value);

	IPW_DEBUG_WX("SET Both Retry Limits -> %d\n", wrqu->retry.value);

      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}