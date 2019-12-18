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
struct dim {int tune_state; int steps_left; int steps_right; } ;

/* Variables and functions */
#define  DIM_GOING_RIGHT 130 
#define  DIM_PARKING_ON_TOP 129 
#define  DIM_PARKING_TIRED 128 

bool dim_on_top(struct dim *dim)
{
	switch (dim->tune_state) {
	case DIM_PARKING_ON_TOP:
	case DIM_PARKING_TIRED:
		return true;
	case DIM_GOING_RIGHT:
		return (dim->steps_left > 1) && (dim->steps_right == 1);
	default: /* DIM_GOING_LEFT */
		return (dim->steps_right > 1) && (dim->steps_left == 1);
	}
}