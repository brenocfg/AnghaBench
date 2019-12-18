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
 int /*<<< orphan*/  console_init () ; 
 int /*<<< orphan*/  real_main () ; 
 int /*<<< orphan*/  zephyr_getchar_init () ; 

void main(void) {
#ifdef CONFIG_CONSOLE_SUBSYS
    console_init();
#else
    zephyr_getchar_init();
#endif
    real_main();
}