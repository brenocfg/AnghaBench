#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct ncsi_dev_priv {TYPE_1__ ndev; int /*<<< orphan*/  lock; int /*<<< orphan*/ * force_channel; int /*<<< orphan*/ * force_package; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t NCSI_ATTR_IFINDEX ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_start_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  ncsi_stop_dev (TYPE_1__*) ; 
 struct ncsi_dev_priv* ndp_from_ifindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_clear_interface_nl(struct sk_buff *msg, struct genl_info *info)
{
	struct ncsi_dev_priv *ndp;
	unsigned long flags;

	if (!info || !info->attrs)
		return -EINVAL;

	if (!info->attrs[NCSI_ATTR_IFINDEX])
		return -EINVAL;

	ndp = ndp_from_ifindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	if (!ndp)
		return -ENODEV;

	/* Clear any override */
	spin_lock_irqsave(&ndp->lock, flags);
	ndp->force_package = NULL;
	ndp->force_channel = NULL;
	spin_unlock_irqrestore(&ndp->lock, flags);
	netdev_info(ndp->ndev.dev, "NCSI: Cleared preferred package/channel\n");

	/* Bounce the NCSI channel to set changes */
	ncsi_stop_dev(&ndp->ndev);
	ncsi_start_dev(&ndp->ndev);

	return 0;
}