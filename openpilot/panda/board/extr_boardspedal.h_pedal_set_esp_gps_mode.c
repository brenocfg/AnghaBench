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
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 

void pedal_set_esp_gps_mode(uint8_t mode) {
  UNUSED(mode);
  puts("Trying to set ESP/GPS mode on pedal. This is not supported.\n");
}