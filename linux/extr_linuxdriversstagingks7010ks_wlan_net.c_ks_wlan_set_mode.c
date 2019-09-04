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
union iwreq_data {scalar_t__ mode; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  operation_mode; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int /*<<< orphan*/  need_commit; TYPE_1__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  MODE_ADHOC ; 
 int /*<<< orphan*/  MODE_INFRASTRUCTURE ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_MODE_SET ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_mode(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *uwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	if (uwrq->mode != IW_MODE_ADHOC &&
	    uwrq->mode != IW_MODE_INFRA)
		return -EINVAL;

	priv->reg.operation_mode = (uwrq->mode == IW_MODE_ADHOC) ?
				    MODE_ADHOC : MODE_INFRASTRUCTURE;
	priv->need_commit |= SME_MODE_SET;

	return -EINPROGRESS;	/* Call commit handler */
}