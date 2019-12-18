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
struct dim {int tired; int tune_state; int profile_ix; int /*<<< orphan*/  steps_left; int /*<<< orphan*/  steps_right; } ;

/* Variables and functions */
#define  DIM_GOING_LEFT 131 
#define  DIM_GOING_RIGHT 130 
 int DIM_ON_EDGE ; 
#define  DIM_PARKING_ON_TOP 129 
#define  DIM_PARKING_TIRED 128 
 int DIM_STEPPED ; 
 int DIM_TOO_TIRED ; 
 int NET_DIM_PARAMS_NUM_PROFILES ; 

__attribute__((used)) static int net_dim_step(struct dim *dim)
{
	if (dim->tired == (NET_DIM_PARAMS_NUM_PROFILES * 2))
		return DIM_TOO_TIRED;

	switch (dim->tune_state) {
	case DIM_PARKING_ON_TOP:
	case DIM_PARKING_TIRED:
		break;
	case DIM_GOING_RIGHT:
		if (dim->profile_ix == (NET_DIM_PARAMS_NUM_PROFILES - 1))
			return DIM_ON_EDGE;
		dim->profile_ix++;
		dim->steps_right++;
		break;
	case DIM_GOING_LEFT:
		if (dim->profile_ix == 0)
			return DIM_ON_EDGE;
		dim->profile_ix--;
		dim->steps_left++;
		break;
	}

	dim->tired++;
	return DIM_STEPPED;
}