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
 int /*<<< orphan*/  RGBLIGHT_MODE_KNIGHT ; 
 int /*<<< orphan*/  initStringData () ; 
 int relativityActive ; 
 int /*<<< orphan*/  relativityTimer ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

void activateRelativity(void)
{
  initStringData();
  rgblight_mode(RGBLIGHT_MODE_KNIGHT);
  relativityTimer = timer_read();
  relativityActive = true;
}