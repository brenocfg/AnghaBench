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
 unsigned int CR_ENABLE ; 
 unsigned int CR_RXE ; 
 unsigned int CR_TXE ; 
 unsigned int FBRD_BDIVFRAC ; 
 int /*<<< orphan*/  GPFSEL1 ; 
 int /*<<< orphan*/  GPPUD ; 
 int /*<<< orphan*/  GPPUDCLK0 ; 
 unsigned int IBRD_BDIVINT ; 
 unsigned int LCRH_FEN ; 
 unsigned int LCRH_WLEN_8BITS ; 
 int UART_BAUD_RATE ; 
 int UART_CLOCK ; 
 int /*<<< orphan*/  UART_CR_REG ; 
 int /*<<< orphan*/  UART_FBRD_REG ; 
 int /*<<< orphan*/  UART_IBRD_REG ; 
 int /*<<< orphan*/  UART_LCRH_REG ; 
 int /*<<< orphan*/  delay (int) ; 
 unsigned int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,unsigned int) ; 

void uart_init(void) {
  unsigned int selector;

  selector = get32(GPFSEL1);
  selector &= ~(7 << 12); // clean gpio14
  selector |= 4 << 12;    // set alt0 for gpio14
  selector &= ~(7 << 15); // clean gpio15
  selector |= 4 << 15;    // set alt0 for gpio15
  put32(GPFSEL1, selector);

  put32(GPPUD, 0);
  delay(150);
  put32(GPPUDCLK0, (1 << 14) | (1 << 15));
  delay(150);
  put32(GPPUDCLK0, 0);

  // Baud rate divisor BAUDDIV = (FUARTCLK/(16 Baud rate)) where FUARTCLK is the
  // UART reference clock frequency. The BAUDDIV is comprised of the integer
  // value IBRD and the fractional value FBRD.
  unsigned int baud = UART_CLOCK * 4 / UART_BAUD_RATE;
  put32(UART_IBRD_REG, ((unsigned int)(baud >> 6)) & IBRD_BDIVINT);
  put32(UART_FBRD_REG, (unsigned int)(baud & 0x3F) & FBRD_BDIVFRAC);

  // Enable FIFO and set word length to 8bits.
  put32(UART_LCRH_REG, LCRH_FEN | LCRH_WLEN_8BITS);

  // Enable UART.
  put32(UART_CR_REG, CR_ENABLE | CR_TXE | CR_RXE);
}