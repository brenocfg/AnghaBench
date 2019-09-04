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
 int /*<<< orphan*/  SPRD_ICLR ; 
 int /*<<< orphan*/  SPRD_IEN ; 
 unsigned int SPRD_IEN_TX_EMPTY ; 
 unsigned int serial_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sprd_stop_tx(struct uart_port *port)
{
	unsigned int ien, iclr;

	iclr = serial_in(port, SPRD_ICLR);
	ien = serial_in(port, SPRD_IEN);

	iclr |= SPRD_IEN_TX_EMPTY;
	ien &= ~SPRD_IEN_TX_EMPTY;

	serial_out(port, SPRD_ICLR, iclr);
	serial_out(port, SPRD_IEN, ien);
}