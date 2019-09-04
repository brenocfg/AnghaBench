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
struct TYPE_2__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct orinoco_private {scalar_t__ wpa_ie_len; int /*<<< orphan*/ * wpa_ie; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int EBUSY ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_get_genie(struct net_device *dev,
				   struct iw_request_info *info,
				   union iwreq_data *wrqu, char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	unsigned long flags;
	int err = 0;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	if ((priv->wpa_ie_len == 0) || (priv->wpa_ie == NULL)) {
		wrqu->data.length = 0;
		goto out;
	}

	if (wrqu->data.length < priv->wpa_ie_len) {
		err = -E2BIG;
		goto out;
	}

	wrqu->data.length = priv->wpa_ie_len;
	memcpy(extra, priv->wpa_ie, priv->wpa_ie_len);

out:
	orinoco_unlock(priv, &flags);
	return err;
}