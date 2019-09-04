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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {scalar_t__ long_retry_limit; scalar_t__ short_retry_limit; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,scalar_t__) ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int IW_RETRY_TYPE ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static int ipw2100_wx_get_retry(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	/*
	 * This can be called at any time.  No action lock required
	 */

	struct ipw2100_priv *priv = libipw_priv(dev);

	wrqu->retry.disabled = 0;	/* can't be disabled */

	if ((wrqu->retry.flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME)
		return -EINVAL;

	if (wrqu->retry.flags & IW_RETRY_LONG) {
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		wrqu->retry.value = priv->long_retry_limit;
	} else {
		wrqu->retry.flags =
		    (priv->short_retry_limit !=
		     priv->long_retry_limit) ?
		    IW_RETRY_LIMIT | IW_RETRY_SHORT : IW_RETRY_LIMIT;

		wrqu->retry.value = priv->short_retry_limit;
	}

	IPW_DEBUG_WX("GET Retry -> %d\n", wrqu->retry.value);

	return 0;
}