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

__attribute__((used)) static void process_nice_level(void) {
#ifdef HAVE_NICE
    int nice_level = (int)config_get_number(CONFIG_SECTION_GLOBAL, "process nice level", 19);
    if(nice(nice_level) == -1) error("Cannot set netdata CPU nice level to %d.", nice_level);
    else debug(D_SYSTEM, "Set netdata nice level to %d.", nice_level);
#endif // HAVE_NICE
}