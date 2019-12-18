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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ergodox_right_led_off (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ergodox_right_led_on (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void indicate_using_led(const uint8_t led, const bool enabled) {
  if (enabled) {
    ergodox_right_led_on(led);
  } else {
    ergodox_right_led_off(led);
  }
}