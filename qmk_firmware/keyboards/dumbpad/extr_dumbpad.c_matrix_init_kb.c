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
 int /*<<< orphan*/  LAYER_INDICATOR_LED_0 ; 
 int /*<<< orphan*/  LAYER_INDICATOR_LED_1 ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  wait_ms (int) ; 
 int /*<<< orphan*/  writePin (int /*<<< orphan*/ ,int) ; 

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  for (int i = 0; i < 2; i++) {
    writePin(LAYER_INDICATOR_LED_0, true);
    writePin(LAYER_INDICATOR_LED_1, false);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, true);
    writePin(LAYER_INDICATOR_LED_1, true);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, true);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, false);
    wait_ms(100);
  }

  matrix_init_user();
}