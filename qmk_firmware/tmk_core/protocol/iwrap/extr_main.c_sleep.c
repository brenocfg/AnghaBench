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
 int /*<<< orphan*/  SLEEP_MODE_PWR_DOWN ; 
 int /*<<< orphan*/  WD_IRQ ; 
 int /*<<< orphan*/  WD_OFF ; 
 int /*<<< orphan*/  WD_SET (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  set_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_bod_disable () ; 
 int /*<<< orphan*/  sleep_cpu () ; 
 int /*<<< orphan*/  sleep_disable () ; 
 int /*<<< orphan*/  sleep_enable () ; 

__attribute__((used)) static void sleep(uint8_t term) {
    WD_SET(WD_IRQ, term);

    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_bod_disable();
    sei();
    sleep_cpu();
    sleep_disable();

    WD_SET(WD_OFF);
}