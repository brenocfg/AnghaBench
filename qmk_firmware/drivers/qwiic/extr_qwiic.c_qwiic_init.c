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
 int /*<<< orphan*/  joystiic_init () ; 
 int /*<<< orphan*/  micro_oled_init () ; 

void qwiic_init(void) {
#ifdef QWIIC_JOYSTIIC_ENABLE
    joystiic_init();
#endif
#ifdef QWIIC_MICRO_OLED_ENABLE
    micro_oled_init();
#endif
}