#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int baud_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  uart_div_modify (int) ; 
 TYPE_1__ uartdev ; 

void _X_uart_init(uint32_t a) {
  // GPIO_FUNC_IN_SEL3
  // xx999999 88888877 77776666 66555555
  // 11111111 11111100 00001111 11111111 = 0xfffc0fff
  // 00000000 00000000 10010000 00000000 = 0x00009000
  // GPIO17 func => 9
  // 00000000 00000010 00000000 00000000
  uart_div_modify(13000000 / uartdev.baud_rate);
  // ...
}