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
union iwreq_data {int /*<<< orphan*/  name; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int config; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int CFG_PREAMBLE_LONG ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ipw_wx_get_preamble(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	if (priv->config & CFG_PREAMBLE_LONG)
		snprintf(wrqu->name, IFNAMSIZ, "long (1)");
	else
		snprintf(wrqu->name, IFNAMSIZ, "auto (0)");
	mutex_unlock(&priv->mutex);
	return 0;
}