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
struct ff_clock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_clock_release (struct ff_clock**) ; 
 struct ff_clock* ff_clock_retain (struct ff_clock*) ; 

struct ff_clock *ff_clock_move(struct ff_clock **clock)
{
	struct ff_clock *retained_clock = ff_clock_retain(*clock);
	ff_clock_release(clock);

	return retained_clock;
}