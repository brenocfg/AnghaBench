#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void** b; void** g; void** r; } ;
struct TYPE_4__ {scalar_t__ scan; TYPE_1__ rgb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_B ; 
 int /*<<< orphan*/  MAX_G ; 
 int /*<<< orphan*/  MAX_R ; 
 int /*<<< orphan*/  MIN_B ; 
 int /*<<< orphan*/  MIN_G ; 
 int /*<<< orphan*/  MIN_R ; 
 void* UNDERGLOW_B ; 
 void* UNDERGLOW_G ; 
 void* UNDERGLOW_R ; 
 scalar_t__ UNDERGLOW_SCAN_CODE ; 
 void* calculate_new_color_component_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* led_cur ; 

__attribute__((used)) static void update_led_cur_rgb_values(void) {
  if (led_cur->scan == UNDERGLOW_SCAN_CODE) {
    *led_cur->rgb.r = UNDERGLOW_R;
    *led_cur->rgb.g = UNDERGLOW_G;
    *led_cur->rgb.b = UNDERGLOW_B;
  } else {
    *led_cur->rgb.r = calculate_new_color_component_value(MAX_R, MIN_R);
    *led_cur->rgb.g = calculate_new_color_component_value(MAX_G, MIN_G);
    *led_cur->rgb.b = calculate_new_color_component_value(MAX_B, MIN_B);
  }
}