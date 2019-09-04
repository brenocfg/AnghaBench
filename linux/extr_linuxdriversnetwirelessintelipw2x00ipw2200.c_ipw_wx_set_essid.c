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
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  flags; } ;
union iwreq_data {TYPE_1__ essid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int essid_len; int status; int /*<<< orphan*/  mutex; int /*<<< orphan*/  essid; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_STATIC_ESSID ; 
 int /*<<< orphan*/  IPW_DEBUG_ASSOC (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,...) ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_ASSOCIATING ; 
 int /*<<< orphan*/  ipw_associate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_disassociate (struct ipw_priv*) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_essid(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
        int length;

        mutex_lock(&priv->mutex);

        if (!wrqu->essid.flags)
        {
                IPW_DEBUG_WX("Setting ESSID to ANY\n");
                ipw_disassociate(priv);
                priv->config &= ~CFG_STATIC_ESSID;
                ipw_associate(priv);
                mutex_unlock(&priv->mutex);
                return 0;
        }

	length = min((int)wrqu->essid.length, IW_ESSID_MAX_SIZE);

	priv->config |= CFG_STATIC_ESSID;

	if (priv->essid_len == length && !memcmp(priv->essid, extra, length)
	    && (priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING))) {
		IPW_DEBUG_WX("ESSID set to current ESSID.\n");
		mutex_unlock(&priv->mutex);
		return 0;
	}

	IPW_DEBUG_WX("Setting ESSID: '%*pE' (%d)\n", length, extra, length);

	priv->essid_len = length;
	memcpy(priv->essid, extra, priv->essid_len);

	/* Network configuration changed -- force [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to ESSID change.\n");
	if (!ipw_disassociate(priv))
		ipw_associate(priv);

	mutex_unlock(&priv->mutex);
	return 0;
}