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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ncsi_dev_priv {int flags; int multi_package; TYPE_1__ ndev; int /*<<< orphan*/  lock; int /*<<< orphan*/  package_whitelist; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 size_t NCSI_ATTR_IFINDEX ; 
 size_t NCSI_ATTR_MULTI_FLAG ; 
 size_t NCSI_ATTR_PACKAGE_MASK ; 
 int NCSI_DEV_HWA ; 
 int NCSI_DEV_RESET ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_reset_dev (TYPE_1__*) ; 
 struct ncsi_dev_priv* ndp_from_ifindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nla_get_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_set_package_mask_nl(struct sk_buff *msg,
				    struct genl_info *info)
{
	struct ncsi_dev_priv *ndp;
	unsigned long flags;
	int rc;

	if (!info || !info->attrs)
		return -EINVAL;

	if (!info->attrs[NCSI_ATTR_IFINDEX])
		return -EINVAL;

	if (!info->attrs[NCSI_ATTR_PACKAGE_MASK])
		return -EINVAL;

	ndp = ndp_from_ifindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	if (!ndp)
		return -ENODEV;

	spin_lock_irqsave(&ndp->lock, flags);
	if (nla_get_flag(info->attrs[NCSI_ATTR_MULTI_FLAG])) {
		if (ndp->flags & NCSI_DEV_HWA) {
			ndp->multi_package = true;
			rc = 0;
		} else {
			netdev_err(ndp->ndev.dev,
				   "NCSI: Can't use multiple packages without HWA\n");
			rc = -EPERM;
		}
	} else {
		ndp->multi_package = false;
		rc = 0;
	}

	if (!rc)
		ndp->package_whitelist =
			nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_MASK]);
	spin_unlock_irqrestore(&ndp->lock, flags);

	if (!rc) {
		/* Update channel configuration */
		if (!(ndp->flags & NCSI_DEV_RESET))
			ncsi_reset_dev(&ndp->ndev);
	}

	return rc;
}