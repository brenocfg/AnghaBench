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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDEA ; 
 scalar_t__ layer_state_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_1_off () ; 
 int /*<<< orphan*/  led_1_on () ; 
 int /*<<< orphan*/  led_3_off () ; 
 int /*<<< orphan*/  led_3_on () ; 

uint32_t layer_state_set_user(uint32_t state) {

    if(layer_state_cmp(state ,IDEA)) {
        led_1_on();
        led_3_on();
    } else {
        led_1_off();
        led_3_off();
    }

  return state;
}