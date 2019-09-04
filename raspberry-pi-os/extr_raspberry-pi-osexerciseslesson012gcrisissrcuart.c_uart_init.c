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

void uart_init (int baudrate)
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

    put32(UART_CR,0);
    //need remove -mgeneral-regs-only in Makefile
    int ibrd = 3000000/baudrate;
    int fbrd = (int)((3000000.0f/baudrate -ibrd)*64.f + 0.5);
    //LCRH must be set behind IBRD and FBRD,please refer to page 3-14 in http://infocenter.arm.com/help/topic/com.arm.doc.ddi0183g/DDI0183G_uart_pl011_r1p5_trm.pdf
	put32(UART_IBRD,ibrd);             //Set baud rate integer part
	put32(UART_FBRD,fbrd);             //Set baud rate frational part
	put32(UART_LCRH,(3<<5));             //Enable 8 bit mode
    put32(UART_IMSC, 0);

	put32(UART_CR,(1<<8)|(1<<9)|1);               //Finally, enable transmitter and receiver
}