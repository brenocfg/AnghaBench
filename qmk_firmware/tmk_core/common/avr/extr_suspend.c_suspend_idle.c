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
 int /*<<< orphan*/  SLEEP_MODE_IDLE ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  set_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_cpu () ; 
 int /*<<< orphan*/  sleep_disable () ; 
 int /*<<< orphan*/  sleep_enable () ; 

void suspend_idle(uint8_t time) {
    cli();
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
}