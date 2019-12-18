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
struct TYPE_2__ {scalar_t__ red_mode; scalar_t__ green_mode; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 scalar_t__ LEDMODE_ON ; 
 int /*<<< orphan*/  LED_GREEN ; 
 int /*<<< orphan*/  LED_RED ; 
 int /*<<< orphan*/  eeconfig_read_user () ; 
 TYPE_1__ led_config ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 

void keyboard_post_init_user(void) {
  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  if(led_config.red_mode == LEDMODE_ON) {
      writePinHigh(LED_RED);
  }

  if(led_config.green_mode == LEDMODE_ON) {
      writePinHigh(LED_GREEN);
  }
}