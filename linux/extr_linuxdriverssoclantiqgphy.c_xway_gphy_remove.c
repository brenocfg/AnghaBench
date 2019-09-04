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
struct xway_gphy_priv {int /*<<< orphan*/  gphy_clk_gate; int /*<<< orphan*/  membase; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xway_gphy_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xway_gphy_remove(struct platform_device *pdev)
{
	struct xway_gphy_priv *priv = platform_get_drvdata(pdev);

	iowrite32be(0, priv->membase);

	clk_disable_unprepare(priv->gphy_clk_gate);

	return 0;
}