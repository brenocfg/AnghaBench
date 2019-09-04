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
 int /*<<< orphan*/  U_CR_REG ; 
 int /*<<< orphan*/  U_FBRD_REG ; 
 int /*<<< orphan*/  U_IBRD_REG ; 
 int /*<<< orphan*/  U_IMSC_REG ; 
 int /*<<< orphan*/  U_LCRH_REG ; 
 int /*<<< orphan*/  delay (int) ; 
 unsigned int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void uart_init (void)
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt0 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt0 for gpio 15
	put32(GPFSEL1, selector);

	put32(GPPUD, 0);
	delay(150);
	put32(GPPUDCLK0, (1<<14) | (1<<15));
	delay(150);
	put32(GPPUDCLK0, 0);

    
	put32(U_CR_REG, 0);                    // disable UART until configuration is done

	/* baud divisor = UARTCLK / (16 * baud_rate) 
	                = 48 * 10^6 / (16 * 115200) = 26.0416666667
       integer part = 26
	   fractional part = (int) ((0.0416666667 * 64) + 0.5) 
	                   = 3
	   generated baud rate divisor = 26 + (3 / 64) = 26.046875
       generated baud rate = (48 * 10^6) / (16 * 26.046875) = 115177
	   error = |(115177 - 115200) / 115200 * 100| = 0.02%
	*/
	put32(U_IBRD_REG, 26);                 // baud rate divisor, integer part
	put32(U_FBRD_REG, 3);                  // baud rate divisor, fractional part
	
	put32(U_LCRH_REG, (1<<4) | (3<<5));    // enable FIFOs and 8 bits frames
	put32(U_IMSC_REG, 0);                  // mask interupts
	put32(U_CR_REG, 1 | (1<<8) | (1<<9));  // enable UART, receive and transmit
}