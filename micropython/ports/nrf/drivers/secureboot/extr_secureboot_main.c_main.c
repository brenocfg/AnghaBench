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
 int /*<<< orphan*/  configure_flash () ; 
 int /*<<< orphan*/  configure_peripherals () ; 
 int /*<<< orphan*/  configure_ram () ; 
 int /*<<< orphan*/  jump_to_non_secure () ; 

int main(void) {
    configure_flash();
    configure_ram();
    configure_peripherals();

    jump_to_non_secure();

    while (1) {
	;
    }

    return 0;
}