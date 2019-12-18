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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  pyb_rtc_get_time (int*,int*) ; 
 int /*<<< orphan*/  rtc_msec_add (int,int*,int*) ; 

void pyb_rtc_calc_future_time (uint32_t a_mseconds, uint32_t *f_seconds, uint16_t *f_mseconds) {
    uint32_t c_seconds;
    uint16_t c_mseconds;
    // get the current time
    pyb_rtc_get_time(&c_seconds, &c_mseconds);
    // calculate the future seconds
    *f_seconds = c_seconds + (a_mseconds / 1000);
    // calculate the "remaining" future mseconds
    *f_mseconds = a_mseconds % 1000;
    // add the current milliseconds
    rtc_msec_add (c_mseconds, f_seconds, f_mseconds);
}