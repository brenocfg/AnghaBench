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
 int /*<<< orphan*/  CAPS_LED_PIN ; 
 int /*<<< orphan*/  NUM_LED_PIN ; 
 int /*<<< orphan*/  SCROLL_LED_PIN ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(CAPS_LED_PIN);
  writePinLow(CAPS_LED_PIN);
  // set NumLock LED to output and low
  setPinOutput(NUM_LED_PIN);
  writePinLow(NUM_LED_PIN);
  // set ScrollLock LED to output and low
  setPinOutput(SCROLL_LED_PIN);
  writePinLow(SCROLL_LED_PIN);
}