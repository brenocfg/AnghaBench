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
 int /*<<< orphan*/  UART_CR ; 
 int /*<<< orphan*/  UART_FBRD ; 
 int /*<<< orphan*/  UART_IBRD ; 
 int /*<<< orphan*/  UART_IMSC ; 
 int /*<<< orphan*/  UART_LCRH ; 
 int /*<<< orphan*/  delay (int) ; 
 unsigned int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void uart_init ( void )
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt0 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt0 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

    put32(UART_CR, 0);                      // Disable UART while we mess around
    put32(UART_IMSC, 0);                    // Disable all interrupts 

    // Assume 48MHz UART Reference Clock (Standard)
    // Calculate UART clock divider per datasheet
    // BAUDDIV = (FUARTCLK/(16 Baud rate))
    //  Note: We get 6 bits of fraction for the baud div
    // 48000000/(16 * 115200) = 3000000/115200 = 26.0416666...
    // Integer part = 26 :)
    // From http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/I54603.html
    // we want floor(0.04166666.. * 64 + 0.5) = 3

    put32(UART_IBRD, 26);
    put32(UART_FBRD, 3);

    // set to 8 bits, enable fifo
    put32(UART_LCRH, (3 << 5) | (1 << 4));

    // Enable RX, TX, UART
    put32(UART_CR, (1 << 9) | (1 << 8) | (1 << 0));
}