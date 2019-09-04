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
struct TYPE_2__ {int flags; scalar_t__ value; scalar_t__ disabled; } ;
union iwreq_data {TYPE_1__ retry; } ;
struct r8192_priv {scalar_t__ retry_rts; scalar_t__ retry_data; int /*<<< orphan*/  wx_mutex; scalar_t__ bHwRadioOff; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_MAX ; 
 scalar_t__ R8192_MAX_RETRY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl92e_commit (struct net_device*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static int _rtl92e_wx_set_retry(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	int err = 0;

	if (priv->bHwRadioOff)
		return 0;

	mutex_lock(&priv->wx_mutex);

	if (wrqu->retry.flags & IW_RETRY_LIFETIME ||
	    wrqu->retry.disabled) {
		err = -EINVAL;
		goto exit;
	}
	if (!(wrqu->retry.flags & IW_RETRY_LIMIT)) {
		err = -EINVAL;
		goto exit;
	}

	if (wrqu->retry.value > R8192_MAX_RETRY) {
		err = -EINVAL;
		goto exit;
	}
	if (wrqu->retry.flags & IW_RETRY_MAX)
		priv->retry_rts = wrqu->retry.value;
	else
		priv->retry_data = wrqu->retry.value;

	rtl92e_commit(dev);
exit:
	mutex_unlock(&priv->wx_mutex);

	return err;
}