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
struct TYPE_2__ {int /*<<< orphan*/  asp; } ;
struct stmmac_priv {int /*<<< orphan*/  sstats; TYPE_1__ dma_cap; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stmmac_global_err (struct stmmac_priv*) ; 
 int stmmac_safety_feat_irq_status (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool stmmac_safety_feat_interrupt(struct stmmac_priv *priv)
{
	int ret;

	ret = stmmac_safety_feat_irq_status(priv, priv->dev,
			priv->ioaddr, priv->dma_cap.asp, &priv->sstats);
	if (ret && (ret != -EINVAL)) {
		stmmac_global_err(priv);
		return true;
	}

	return false;
}