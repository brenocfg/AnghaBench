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
typedef  int u32 ;
typedef  int u16 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ MEN_Z135_TX_CTRL ; 
 unsigned int TIOCSER_TEMT ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static unsigned int men_z135_tx_empty(struct uart_port *port)
{
	u32 wptr;
	u16 txc;

	wptr = ioread32(port->membase + MEN_Z135_TX_CTRL);
	txc = (wptr >> 16) & 0x3ff;

	if (txc == 0)
		return TIOCSER_TEMT;
	else
		return 0;
}