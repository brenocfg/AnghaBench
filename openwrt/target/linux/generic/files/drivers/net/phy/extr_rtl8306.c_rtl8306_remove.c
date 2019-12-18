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
struct rtl_priv {int /*<<< orphan*/  dev; } ;
struct phy_device {struct rtl_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rtl_priv*) ; 
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtl8306_remove(struct phy_device *pdev)
{
	struct rtl_priv *priv = pdev->priv;
	unregister_switch(&priv->dev);
	kfree(priv);
}