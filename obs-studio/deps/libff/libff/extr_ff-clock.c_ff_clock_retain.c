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
struct ff_clock {int /*<<< orphan*/  retain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_atomic_inc_long (int /*<<< orphan*/ *) ; 

struct ff_clock *ff_clock_retain(struct ff_clock *clock)
{
	ff_atomic_inc_long(&clock->retain);

	return clock;
}