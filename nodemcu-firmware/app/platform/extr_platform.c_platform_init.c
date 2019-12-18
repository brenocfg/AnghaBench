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
 int PLATFORM_OK ; 
 int /*<<< orphan*/  cmn_platform_init () ; 
 int /*<<< orphan*/  get_pin_map () ; 

int platform_init()
{
  // Setup the various forward and reverse mappings for the pins
  get_pin_map();

  cmn_platform_init();
  // All done
  return PLATFORM_OK;
}