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
 int /*<<< orphan*/  dprintf (char*) ; 
 int initialized ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

void matrix_init_user(void) {
  if (!initialized){
      dprintf("Initializing in matrix_scan_user");
      rgblight_enable();
      rgblight_mode(7);
      rgblight_sethsv(0,255,255);
      rgblight_setrgb(0x00, 0x00, 0xFF);
      initialized = 1;
    }
}