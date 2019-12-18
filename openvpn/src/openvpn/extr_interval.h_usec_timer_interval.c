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
struct usec_timer {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  USEC_TIMER_MAX ; 
 int tv_subtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
usec_timer_interval(struct usec_timer *obj)
{
    return tv_subtract(&obj->end, &obj->start, USEC_TIMER_MAX);
}