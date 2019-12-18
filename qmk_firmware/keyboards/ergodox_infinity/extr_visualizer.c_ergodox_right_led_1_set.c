#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  led1; } ;

/* Variables and functions */
 TYPE_1__ user_data_keyboard ; 
 int /*<<< orphan*/  visualizer_set_user_data (TYPE_1__*) ; 

void ergodox_right_led_1_set(uint8_t n) {
    user_data_keyboard.led1 = n;
    visualizer_set_user_data(&user_data_keyboard);
}