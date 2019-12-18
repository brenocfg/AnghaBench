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
 int /*<<< orphan*/  BLUE_LED ; 
 int /*<<< orphan*/  GREEN_LED ; 
 int /*<<< orphan*/  RED_LED ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void turn_off_leds(void)
{
    writePinLow(RED_LED);
    writePinLow(BLUE_LED);
    writePinLow(GREEN_LED);
}