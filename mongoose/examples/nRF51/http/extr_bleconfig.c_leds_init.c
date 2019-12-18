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
 int /*<<< orphan*/  ALL_APP_LED ; 
 int /*<<< orphan*/  LEDS_CONFIGURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEDS_OFF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void leds_init(void)
{
  // Configure application LED pins.
  LEDS_CONFIGURE(ALL_APP_LED);

  // Turn off all LED on initialization.
  LEDS_OFF(ALL_APP_LED);
}