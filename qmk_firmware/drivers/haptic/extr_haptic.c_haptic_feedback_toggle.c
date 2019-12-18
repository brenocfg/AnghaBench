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
struct TYPE_2__ {scalar_t__ feedback; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 scalar_t__ HAPTIC_FEEDBACK_MAX ; 
 scalar_t__ KEY_PRESS ; 
 int /*<<< orphan*/  eeconfig_update_haptic (int /*<<< orphan*/ ) ; 
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void haptic_feedback_toggle(void) {
    haptic_config.feedback++;
    if (haptic_config.feedback >= HAPTIC_FEEDBACK_MAX) haptic_config.feedback = KEY_PRESS;
    xprintf("haptic_config.feedback = %u\n", !haptic_config.feedback);
    eeconfig_update_haptic(haptic_config.raw);
}