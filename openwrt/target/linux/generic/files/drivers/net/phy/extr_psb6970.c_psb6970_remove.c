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
struct psb6970_priv {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct phy_device {TYPE_1__ mdio; struct psb6970_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct psb6970_priv*) ; 
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psb6970_remove(struct phy_device *pdev)
{
	struct psb6970_priv *priv = pdev->priv;

	if (!priv)
		return;

	if (pdev->mdio.addr == 0)
		unregister_switch(&priv->dev);
	kfree(priv);
}