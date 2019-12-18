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
 int lpc_console ; 
 int /*<<< orphan*/  lpc_uart_init () ; 
 int potato_console ; 
 int /*<<< orphan*/  potato_uart_init () ; 

void uart_init_ppc(int lpc) {
    lpc_console = lpc;

    if (!lpc_console) {
        potato_console = 1;

        potato_uart_init();
    } else {
        lpc_uart_init();
    }
}