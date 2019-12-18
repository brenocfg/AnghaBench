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
typedef  int uint32_t ;

/* Variables and functions */
 int REG_READ (int /*<<< orphan*/ ) ; 
 int UART_CLKDIV_FRAG_S ; 
 int UART_CLKDIV_FRAG_V ; 
 int UART_CLKDIV_M ; 
 int /*<<< orphan*/  UART_CLKDIV_REG (int) ; 
 int /*<<< orphan*/  uart_div_modify (int,int) ; 

uint32_t set_baud_rate(uint32_t uart_no, uint32_t old_baud_rate,
                       uint32_t new_baud_rate) {
  uint32_t uart_reg = REG_READ(UART_CLKDIV_REG(uart_no));
  uint32_t uart_div = uart_reg & UART_CLKDIV_M;
  uint32_t fraction = (uart_reg >> UART_CLKDIV_FRAG_S) & UART_CLKDIV_FRAG_V;
  uart_div = (uart_div << 4) + fraction;
  uint32_t master_freq = uart_div * old_baud_rate;
  uart_div_modify(uart_no, master_freq / new_baud_rate);
  return uart_div;
}