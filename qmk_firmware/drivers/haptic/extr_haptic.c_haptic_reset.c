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
typedef  void* uint8_t ;
struct TYPE_2__ {int enable; void* mode; void* feedback; int /*<<< orphan*/  raw; void* dwell; } ;

/* Variables and functions */
 void* HAPTIC_FEEDBACK_DEFAULT ; 
 void* HAPTIC_MODE_DEFAULT ; 
 void* SOLENOID_DEFAULT_DWELL ; 
 int /*<<< orphan*/  eeconfig_update_haptic (int /*<<< orphan*/ ) ; 
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  xprintf (char*,void*) ; 

void haptic_reset(void) {
    haptic_config.enable   = true;
    uint8_t feedback       = HAPTIC_FEEDBACK_DEFAULT;
    haptic_config.feedback = feedback;
#ifdef DRV2605L
    uint8_t mode       = HAPTIC_MODE_DEFAULT;
    haptic_config.mode = mode;
#endif
#ifdef SOLENOID_ENABLE
    uint8_t dwell       = SOLENOID_DEFAULT_DWELL;
    haptic_config.dwell = dwell;
#endif
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.feedback = %u\n", haptic_config.feedback);
    xprintf("haptic_config.mode = %u\n", haptic_config.mode);
}