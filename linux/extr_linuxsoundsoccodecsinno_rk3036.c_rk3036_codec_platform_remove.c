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
struct rk3036_codec_priv {int /*<<< orphan*/  pclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct rk3036_codec_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk3036_codec_platform_remove(struct platform_device *pdev)
{
	struct rk3036_codec_priv *priv = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(priv->pclk);

	return 0;
}