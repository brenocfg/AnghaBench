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
 int get_el () ; 
 int /*<<< orphan*/  init_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  putc ; 
 int /*<<< orphan*/  uart_init () ; 
 int /*<<< orphan*/  uart_recv () ; 
 int /*<<< orphan*/  uart_send (int /*<<< orphan*/ ) ; 

void kernel_main(void) {
  uart_init();
  init_printf(0, putc);
  int el = get_el();
  printf("Exception level: %d \r\n", el);

  while (1) {
    uart_send(uart_recv());
  }
}