#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int uartclk; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct pcmcia_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void quirk_setup_brainboxes_0104(struct pcmcia_device *link, struct uart_8250_port *uart)
{
	uart->port.uartclk = 14745600;
}