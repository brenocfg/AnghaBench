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
 int /*<<< orphan*/  RTCD1 ; 
 int /*<<< orphan*/  backlight_init_ports () ; 
 int /*<<< orphan*/  eeprom_init_kb () ; 
 int /*<<< orphan*/  last_timespec ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int queue_for_send ; 
 int /*<<< orphan*/  rtcGetTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void matrix_init_kb(void)
{
	eeprom_init_kb();
  rtcGetTime(&RTCD1, &last_timespec);
  queue_for_send = true;
  backlight_init_ports();
	matrix_init_user();
}