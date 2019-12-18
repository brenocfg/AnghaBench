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
struct event_timeout {scalar_t__ n; scalar_t__ defined; } ;
typedef  scalar_t__ interval_t ;

/* Variables and functions */

__attribute__((used)) static inline void
event_timeout_modify_wakeup(struct event_timeout *et, interval_t n)
{
    /* note that you might need to call reset_coarse_timers after this */
    if (et->defined)
    {
        et->n = (n >= 0) ? n : 0;
    }
}