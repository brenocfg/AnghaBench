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
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void shutdown_user() {
  // Shutdown the layer LEDs
  writePinLow(LAYER_INDICATOR_LED_0);
  writePinLow(LAYER_INDICATOR_LED_1);
}