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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int BACKLIGHT_LEVELS ; 
 int /*<<< orphan*/  PWMD3 ; 
 int /*<<< orphan*/  PWM_FRACTION_TO_WIDTH (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ cie_lightness (int) ; 
 int /*<<< orphan*/  is_breathing () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  pwmDisableChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwmEnableChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void backlight_set(uint8_t level) {
    printf("backlight_set(%d)\n", level);
    uint32_t duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) level / BACKLIGHT_LEVELS));
    printf("duty: (%d)\n", duty);
    if (level == 0) {
        // Turn backlight off
        pwmDisableChannel(&PWMD3, 0);
    } else {
      // Turn backlight on
      if(!is_breathing()){
        pwmEnableChannel(&PWMD3, 0, PWM_FRACTION_TO_WIDTH(&PWMD3,0xFFFF,duty));
      }
    }
}