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
struct platform_device {int dummy; } ;
struct asm9260_wdt_priv {int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk; int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  asm9260_wdt_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct asm9260_wdt_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asm9260_wdt_remove(struct platform_device *pdev)
{
	struct asm9260_wdt_priv *priv = platform_get_drvdata(pdev);

	asm9260_wdt_disable(&priv->wdd);

	watchdog_unregister_device(&priv->wdd);

	clk_disable_unprepare(priv->clk);
	clk_disable_unprepare(priv->clk_ahb);

	return 0;
}