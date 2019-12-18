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
typedef  size_t uint8_t ;

/* Variables and functions */
 int* diablo_key_time ; 
 int /*<<< orphan*/ * diablo_timer ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 

bool check_dtimer(uint8_t dtimer) { return (timer_elapsed(diablo_timer[dtimer]) < (diablo_key_time[dtimer] * 1000)) ? false : true; }