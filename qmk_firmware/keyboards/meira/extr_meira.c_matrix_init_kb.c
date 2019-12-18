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
 int /*<<< orphan*/  WDTO_500MS ; 
 int /*<<< orphan*/  backlight_set (int) ; 
 int debug_enable ; 
 int /*<<< orphan*/  issi_init () ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  wdt_enable (int /*<<< orphan*/ ) ; 

void matrix_init_kb(void)
{
    debug_enable=true;
    print("meira matrix_init_kb\n");

#ifdef ISSI_ENABLE
    issi_init();
#endif
    backlight_set(5);
#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif

    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
}