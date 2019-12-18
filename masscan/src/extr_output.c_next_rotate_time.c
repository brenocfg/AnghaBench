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
typedef  unsigned int time_t ;

/* Variables and functions */

__attribute__((used)) static time_t
next_rotate_time(time_t last_rotate, unsigned period, unsigned offset)
{
    time_t next;

    next = last_rotate - (last_rotate % period) + period + offset;

    return next;
}