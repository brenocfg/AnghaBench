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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC16IS7XX_IER_THRI_BIT ; 
 int /*<<< orphan*/  sc16is7xx_ier_clear (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc16is7xx_stop_tx(struct uart_port *port)
{
	sc16is7xx_ier_clear(port, SC16IS7XX_IER_THRI_BIT);
}