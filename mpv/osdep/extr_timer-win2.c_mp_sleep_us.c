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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 

void mp_sleep_us(int64_t us)
{
    if (us < 0)
        return;
    // Sleep(0) won't sleep for one clocktick as the unix usleep
    // instead it will only make the thread ready
    // it may take some time until it actually starts to run again
    if (us < 1000)
        us = 1000;
    Sleep(us / 1000);
}