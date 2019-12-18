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
struct TYPE_2__ {scalar_t__ buzz; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLENOID_PIN ; 
 TYPE_1__ haptic_config ; 
 int solenoid_buzzing ; 
 int solenoid_on ; 
 int /*<<< orphan*/  solenoid_start ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 

void solenoid_fire(void) {
    if (!haptic_config.buzz && solenoid_on) return;
    if (haptic_config.buzz && solenoid_buzzing) return;

    solenoid_on      = true;
    solenoid_buzzing = true;
    solenoid_start   = timer_read();
    writePinHigh(SOLENOID_PIN);
}