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
 int console_getchar () ; 
 int zephyr_getchar () ; 

int mp_hal_stdin_rx_chr(void) {
#ifdef CONFIG_CONSOLE_SUBSYS
    return console_getchar();
#else
    return zephyr_getchar();
#endif
}