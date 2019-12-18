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
 scalar_t__ SERVERS_CYCLE_TIME_MS ; 
 int /*<<< orphan*/  mp_hal_delay_ms (scalar_t__) ; 
 int sleep_sockets ; 

void server_sleep_sockets (void) {
    sleep_sockets = true;
    mp_hal_delay_ms(SERVERS_CYCLE_TIME_MS + 1);
}