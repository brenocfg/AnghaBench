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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; scalar_t__ disabled; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_4__ {int manual_retry_count; TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
typedef  scalar_t__ __le16 ;
struct TYPE_3__ {scalar_t__ (* get_rid ) (struct net_device*,int /*<<< orphan*/ ,scalar_t__*,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFA384X_RID_CNFALTRETRYCOUNT ; 
 int /*<<< orphan*/  HFA384X_RID_LONGRETRYLIMIT ; 
 int /*<<< orphan*/  HFA384X_RID_MAXTRANSMITLIFETIME ; 
 int /*<<< orphan*/  HFA384X_RID_SHORTRETRYLIMIT ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int IW_RETRY_TYPE ; 
 int le16_to_cpu (scalar_t__) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 scalar_t__ stub2 (struct net_device*,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 scalar_t__ stub3 (struct net_device*,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 scalar_t__ stub4 (struct net_device*,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 

__attribute__((used)) static int prism2_ioctl_giwretry(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *rrq, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	__le16 shortretry, longretry, lifetime, altretry;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->func->get_rid(dev, HFA384X_RID_SHORTRETRYLIMIT, &shortretry,
				 2, 1) < 0 ||
	    local->func->get_rid(dev, HFA384X_RID_LONGRETRYLIMIT, &longretry,
				 2, 1) < 0 ||
	    local->func->get_rid(dev, HFA384X_RID_MAXTRANSMITLIFETIME,
				 &lifetime, 2, 1) < 0)
		return -EINVAL;

	rrq->disabled = 0;

	if ((rrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) {
		rrq->flags = IW_RETRY_LIFETIME;
		rrq->value = le16_to_cpu(lifetime) * 1024;
	} else {
		if (local->manual_retry_count >= 0) {
			rrq->flags = IW_RETRY_LIMIT;
			if (local->func->get_rid(dev,
						 HFA384X_RID_CNFALTRETRYCOUNT,
						 &altretry, 2, 1) >= 0)
				rrq->value = le16_to_cpu(altretry);
			else
				rrq->value = local->manual_retry_count;
		} else if ((rrq->flags & IW_RETRY_LONG)) {
			rrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
			rrq->value = le16_to_cpu(longretry);
		} else {
			rrq->flags = IW_RETRY_LIMIT;
			rrq->value = le16_to_cpu(shortretry);
			if (shortretry != longretry)
				rrq->flags |= IW_RETRY_SHORT;
		}
	}
	return 0;
}