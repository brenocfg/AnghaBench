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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  pyb_rtc_get_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint32_t pyb_rtc_get_seconds (void) {
    uint32_t seconds;
    uint16_t mseconds;
    pyb_rtc_get_time(&seconds, &mseconds);
    return seconds;
}