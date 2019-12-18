#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int buzz; } ;

/* Variables and functions */
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  haptic_set_buzz (int) ; 

void haptic_buzz_toggle(void) {
    bool buzz_stat     = !haptic_config.buzz;
    haptic_config.buzz = buzz_stat;
    haptic_set_buzz(buzz_stat);
}