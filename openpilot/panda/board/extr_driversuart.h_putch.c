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
 scalar_t__ has_external_debug_serial ; 
 int /*<<< orphan*/  injectc (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  putc (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  uart_ring_debug ; 

void putch(const char a) {
  if (has_external_debug_serial) {
    // assuming debugging is important if there's external serial connected
    while (!putc(&uart_ring_debug, a));

  } else {
    // misra-c2012-17.7: serial debug function, ok to ignore output
    (void)injectc(&uart_ring_debug, a);
  }
}