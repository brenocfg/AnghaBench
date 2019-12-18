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

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IIR_REG ; 
 int IIR_REG_REC_NON_EMPTY ; 
 int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_recv () ; 
 int /*<<< orphan*/  uart_send (int /*<<< orphan*/ ) ; 

void handle_uart_irq( void )
{
	// There may be more than one byte in the FIFO.
	while((get32(AUX_MU_IIR_REG) & IIR_REG_REC_NON_EMPTY) ==
	      IIR_REG_REC_NON_EMPTY) {
		uart_send(uart_recv()); 
	}
}