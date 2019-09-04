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
 unsigned long cur_proc ; 
 unsigned long getmpid () ; 
 int /*<<< orphan*/  uart_init () ; 
 unsigned long uart_recv () ; 
 int /*<<< orphan*/  uart_send (unsigned long) ; 
 int /*<<< orphan*/  uart_send_string (char*) ; 

void kernel_main(void) {
  unsigned long mpid = getmpid();

  // Only init UART on proc #0
  if (mpid == 0) {
    uart_init();
  }

  // Wait for previous proc to finish printing their message.
  while (cur_proc != mpid)
    ;

  uart_send_string("Hello, from processor ");
  uart_send(mpid + '0');
  uart_send_string("\r\n");

  // Signal the next proc to go.
  ++cur_proc;

  // Only proc #0 handles echo
  if (mpid == 0) {
    while (cur_proc != 4)
      ;

    while (1) {
      uart_send(uart_recv());
    }
  }
}