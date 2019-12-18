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
 int WDOG_TMROUTL ; 
 int /*<<< orphan*/  k20x_clock_init () ; 

void __early_init(void) {
    // This is a dirty hack and should only be used as a temporary fix until this
    // is upstreamed.
    while (WDOG_TMROUTL < 2)
        ;  // Must wait for WDOG timer if already running, before jumping

    k20x_clock_init();
}