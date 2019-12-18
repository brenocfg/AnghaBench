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

/* Variables and functions */
 int /*<<< orphan*/  GCR ; 
 int /*<<< orphan*/  GCR_ACLINK_OFF ; 
 int /*<<< orphan*/  IRQ_AC97 ; 
 int /*<<< orphan*/ * ac97_clk ; 
 int /*<<< orphan*/ * ac97conf_clk ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_is_pxa27x () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_gpio ; 

void pxa2xx_ac97_hw_remove(struct platform_device *dev)
{
	if (cpu_is_pxa27x())
		gpio_free(reset_gpio);
	GCR |= GCR_ACLINK_OFF;
	free_irq(IRQ_AC97, NULL);
	if (ac97conf_clk) {
		clk_put(ac97conf_clk);
		ac97conf_clk = NULL;
	}
	clk_disable_unprepare(ac97_clk);
	clk_put(ac97_clk);
	ac97_clk = NULL;
}