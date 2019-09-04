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
struct platform_device {size_t id; } ;
struct mxs_auart_port {int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  auart_driver ; 
 int /*<<< orphan*/ ** auart_port ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ is_asm9260_auart (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_free_gpio_irq (struct mxs_auart_port*) ; 
 struct mxs_auart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxs_auart_remove(struct platform_device *pdev)
{
	struct mxs_auart_port *s = platform_get_drvdata(pdev);

	uart_remove_one_port(&auart_driver, &s->port);
	auart_port[pdev->id] = NULL;
	mxs_auart_free_gpio_irq(s);
	if (is_asm9260_auart(s)) {
		clk_disable_unprepare(s->clk);
		clk_disable_unprepare(s->clk_ahb);
	}

	return 0;
}