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
struct owl_uart_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void owl_uart_change_baudrate(struct owl_uart_port *owl_port,
				     unsigned long baud)
{
	clk_set_rate(owl_port->clk, baud * 8);
}