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
typedef  int uint8_t ;
struct TYPE_2__ {int amplitude; } ;

/* Variables and functions */
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  haptic_set_amplitude (int) ; 

void haptic_cont_decrease(void) {
    uint8_t amp = haptic_config.amplitude - 10;
    if (haptic_config.amplitude < 20) {
        amp = 20;
    }
    haptic_set_amplitude(amp);
}