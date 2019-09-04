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
typedef  int /*<<< orphan*/  u16 ;
struct hermes {int dummy; } ;
struct orinoco_private {int /*<<< orphan*/  has_sensitivity; struct hermes hw; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {scalar_t__ fixed; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HERMES_RID_CNFSYSTEMSCALE ; 
 int /*<<< orphan*/  USER_BAP ; 
 int hermes_read_wordrec (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_getsens(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *srq,
				 char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	struct hermes *hw = &priv->hw;
	u16 val;
	int err;
	unsigned long flags;

	if (!priv->has_sensitivity)
		return -EOPNOTSUPP;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;
	err = hermes_read_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFSYSTEMSCALE, &val);
	orinoco_unlock(priv, &flags);

	if (err)
		return err;

	srq->value = val;
	srq->fixed = 0; /* auto */

	return 0;
}