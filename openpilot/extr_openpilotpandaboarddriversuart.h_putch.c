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
 int /*<<< orphan*/  debug_ring ; 
 scalar_t__ has_external_debug_serial ; 
 int /*<<< orphan*/  injectc (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  putc (int /*<<< orphan*/ *,char const) ; 

void putch(const char a) {
  if (has_external_debug_serial) {
    /*while ((debug_ring.uart->SR & USART_SR_TXE) == 0);
    debug_ring.uart->DR = a;*/

    // assuming debugging is important if there's external serial connected
    while (!putc(&debug_ring, a));

    //putc(&debug_ring, a);
  } else {
    injectc(&debug_ring, a);
  }
}