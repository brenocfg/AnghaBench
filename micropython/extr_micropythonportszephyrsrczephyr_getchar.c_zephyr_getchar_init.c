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
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  console_irq_input_hook ; 
 int /*<<< orphan*/  k_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_console_in_debug_hook_install (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_register_input (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_sem ; 

void zephyr_getchar_init(void) {
    k_sem_init(&uart_sem, 0, UINT_MAX);
    uart_console_in_debug_hook_install(console_irq_input_hook);
    // All NULLs because we're interested only in the callback above
    uart_register_input(NULL, NULL, NULL);
}