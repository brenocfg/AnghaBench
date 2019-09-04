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
struct stm32_dwmac {int /*<<< orphan*/  clk_rx; int /*<<< orphan*/  clk_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32mcu_suspend(struct stm32_dwmac *dwmac)
{
	clk_disable_unprepare(dwmac->clk_tx);
	clk_disable_unprepare(dwmac->clk_rx);

	return 0;
}