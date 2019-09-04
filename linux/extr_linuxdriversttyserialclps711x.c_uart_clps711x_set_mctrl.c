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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct clps711x_port {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 struct clps711x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mctrl_gpio_set (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void uart_clps711x_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct clps711x_port *s = dev_get_drvdata(port->dev);

	mctrl_gpio_set(s->gpios, mctrl);
}