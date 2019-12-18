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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int id32; int /*<<< orphan*/ * id8; int /*<<< orphan*/ * id16; } ;
typedef  TYPE_1__ rng_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  pyb_rtc_get_time (int*,scalar_t__*) ; 
 int s_seed ; 
 int /*<<< orphan*/  wlan_get_mac (int /*<<< orphan*/ *) ; 

void rng_init0 (void) {
    rng_id_t juggler;
    uint32_t seconds;
    uint16_t mseconds;

    // get the seconds and the milliseconds from the RTC
    pyb_rtc_get_time(&seconds, &mseconds);

    wlan_get_mac (juggler.id8);

    // flatten the 48-bit board identification to 24 bits
    juggler.id16[0] ^= juggler.id16[2];

    juggler.id8[0]  ^= juggler.id8[3];
    juggler.id8[1]  ^= juggler.id8[4];
    juggler.id8[2]  ^= juggler.id8[5];

    s_seed = juggler.id32 & 0x00FFFFFF;
    s_seed += (seconds & 0x000FFFFF) + mseconds;

    // the seed must not be zero
    if (s_seed == 0) {
        s_seed = 1;
    }
}