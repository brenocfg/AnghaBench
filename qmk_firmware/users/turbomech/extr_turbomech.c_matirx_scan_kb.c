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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int RGB_INIT ; 
 int /*<<< orphan*/  RGB_current_mode ; 
 int TOG_STATUS ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 

void matirx_scan_kb (void) {
  if (RGB_INIT) {}
  else {
    RGB_current_mode = rgblight_config.mode;
    RGB_INIT = true;
        }
  rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
  TOG_STATUS = false;
}