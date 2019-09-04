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
struct watchdog_device {int dummy; } ;
struct ts72xx_wdt_priv {int /*<<< orphan*/  control_reg; int /*<<< orphan*/  regval; int /*<<< orphan*/  feed_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS72XX_WDT_FEED_VAL ; 
 struct ts72xx_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts72xx_wdt_start(struct watchdog_device *wdd)
{
	struct ts72xx_wdt_priv *priv = watchdog_get_drvdata(wdd);

	writeb(TS72XX_WDT_FEED_VAL, priv->feed_reg);
	writeb(priv->regval, priv->control_reg);

	return 0;
}