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
struct asm9260_wdt_priv {int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  asm9260_wdt_disable (int /*<<< orphan*/ *) ; 
 struct asm9260_wdt_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void asm9260_wdt_shutdown(struct platform_device *pdev)
{
	struct asm9260_wdt_priv *priv = platform_get_drvdata(pdev);

	asm9260_wdt_disable(&priv->wdd);
}