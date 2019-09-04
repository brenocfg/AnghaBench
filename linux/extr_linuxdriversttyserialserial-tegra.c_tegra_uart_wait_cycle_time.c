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
struct tegra_uart_port {int current_baud; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_uart_wait_cycle_time(struct tegra_uart_port *tup,
				       unsigned int cycles)
{
	if (tup->current_baud)
		udelay(DIV_ROUND_UP(cycles * 1000000, tup->current_baud * 16));
}