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
struct ravb_private {int /*<<< orphan*/  emac_irq; int /*<<< orphan*/ * napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int /*<<< orphan*/  ECMR_MPDE ; 
 size_t RAVB_BE ; 
 size_t RAVB_NC ; 
 int disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int ravb_close (struct net_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_wol_restore(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	int ret;

	napi_enable(&priv->napi[RAVB_NC]);
	napi_enable(&priv->napi[RAVB_BE]);

	/* Disable MagicPacket */
	ravb_modify(ndev, ECMR, ECMR_MPDE, 0);

	ret = ravb_close(ndev);
	if (ret < 0)
		return ret;

	return disable_irq_wake(priv->emac_irq);
}