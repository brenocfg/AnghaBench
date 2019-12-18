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
 scalar_t__ MCUSR ; 
 int /*<<< orphan*/  force_issi_refresh () ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  set_rgb (int,int,int,int) ; 
 int /*<<< orphan*/  wdt_disable () ; 
 int /*<<< orphan*/  wdt_reset () ; 

void reset_keyboard_kb(){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    set_rgb(31, 0x00, 0xFF, 0xFF);
    set_rgb(32, 0x00, 0xFF, 0xFF);
    force_issi_refresh();
    reset_keyboard();
}