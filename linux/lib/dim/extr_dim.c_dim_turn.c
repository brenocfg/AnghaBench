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
struct dim {int tune_state; int /*<<< orphan*/  steps_right; int /*<<< orphan*/  steps_left; } ;

/* Variables and functions */
#define  DIM_GOING_LEFT 131 
#define  DIM_GOING_RIGHT 130 
#define  DIM_PARKING_ON_TOP 129 
#define  DIM_PARKING_TIRED 128 

void dim_turn(struct dim *dim)
{
	switch (dim->tune_state) {
	case DIM_PARKING_ON_TOP:
	case DIM_PARKING_TIRED:
		break;
	case DIM_GOING_RIGHT:
		dim->tune_state = DIM_GOING_LEFT;
		dim->steps_left = 0;
		break;
	case DIM_GOING_LEFT:
		dim->tune_state = DIM_GOING_RIGHT;
		dim->steps_right = 0;
		break;
	}
}