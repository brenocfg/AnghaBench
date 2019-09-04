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
struct csio_sge {int* timer_val; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int INT_MAX ; 

__attribute__((used)) static int
csio_closest_timer(struct csio_sge *s, int time)
{
	int i, delta, match = 0, min_delta = INT_MAX;

	for (i = 0; i < ARRAY_SIZE(s->timer_val); i++) {
		delta = time - s->timer_val[i];
		if (delta < 0)
			delta = -delta;
		if (delta < min_delta) {
			min_delta = delta;
			match = i;
		}
	}
	return match;
}