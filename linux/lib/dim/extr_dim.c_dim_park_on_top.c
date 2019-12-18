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
struct dim {int /*<<< orphan*/  tune_state; scalar_t__ tired; scalar_t__ steps_left; scalar_t__ steps_right; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_PARKING_ON_TOP ; 

void dim_park_on_top(struct dim *dim)
{
	dim->steps_right  = 0;
	dim->steps_left   = 0;
	dim->tired        = 0;
	dim->tune_state   = DIM_PARKING_ON_TOP;
}