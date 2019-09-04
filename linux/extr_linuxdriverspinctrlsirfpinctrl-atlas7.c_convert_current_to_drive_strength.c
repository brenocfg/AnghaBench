#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ ma; scalar_t__ ds_4we; scalar_t__ ds_16st; scalar_t__ ds_0204m31; scalar_t__ ds_0610m31; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ DS_NULL ; 
 scalar_t__ PAD_T_16ST ; 
 scalar_t__ PAD_T_4WE_PD ; 
 scalar_t__ PAD_T_4WE_PU ; 
 scalar_t__ PAD_T_M31_0204_PD ; 
 scalar_t__ PAD_T_M31_0204_PU ; 
 scalar_t__ PAD_T_M31_0610_PD ; 
 scalar_t__ PAD_T_M31_0610_PU ; 
 TYPE_1__* atlas7_ma2ds_map ; 

__attribute__((used)) static u32 convert_current_to_drive_strength(u32 type, u32 ma)
{
	int idx;

	for (idx = 0; idx < ARRAY_SIZE(atlas7_ma2ds_map); idx++) {
		if (atlas7_ma2ds_map[idx].ma != ma)
			continue;

		if (type == PAD_T_4WE_PD || type == PAD_T_4WE_PU)
			return atlas7_ma2ds_map[idx].ds_4we;
		else if (type == PAD_T_16ST)
			return atlas7_ma2ds_map[idx].ds_16st;
		else if (type == PAD_T_M31_0204_PD || type == PAD_T_M31_0204_PU)
			return atlas7_ma2ds_map[idx].ds_0204m31;
		else if (type == PAD_T_M31_0610_PD || type == PAD_T_M31_0610_PU)
			return atlas7_ma2ds_map[idx].ds_0610m31;
	}

	return DS_NULL;
}