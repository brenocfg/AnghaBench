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
union iwreq_data {int /*<<< orphan*/  mode; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ operation_mode; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_1__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 scalar_t__ MODE_INFRASTRUCTURE ; 
 scalar_t__ SLP_SLEEP ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_mode(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *uwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* If not managed, assume it's ad-hoc */
	uwrq->mode = (priv->reg.operation_mode == MODE_INFRASTRUCTURE) ?
		      IW_MODE_INFRA : IW_MODE_ADHOC;

	return 0;
}