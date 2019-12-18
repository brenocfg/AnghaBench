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
 int /*<<< orphan*/  GPFSEL1 ; 
 int /*<<< orphan*/  GPPUD ; 
 int /*<<< orphan*/  GPPUDCLK0 ; 
 int /*<<< orphan*/  UART_CTRL_REG ; 
 int UART_FBRD ; 
 int /*<<< orphan*/  UART_FBRD_REG ; 
 int UART_IBRD ; 
 int /*<<< orphan*/  UART_IBRD_REG ; 
 int /*<<< orphan*/  UART_LCRH_REG ; 
 int /*<<< orphan*/  delay (int) ; 
 unsigned int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void uart_init ( void )
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt5 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	//At startup uart is disabled by default	
	put32(UART_IBRD_REG, UART_IBRD);         //Change baudrate in peripherals/uart_pl011.h
	put32(UART_FBRD_REG, UART_FBRD); 
	put32(UART_LCRH_REG, 0x70);              //Uart hardcoded for for 8 bit mode - no parity - fifo enable
	put32(UART_CTRL_REG, 0x301);             //Enable uart, RX and TX
}