#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ shft; scalar_t__ gain_min; } ;
struct TYPE_3__ {scalar_t__ shft; scalar_t__ gain_min; } ;
struct vpfe_ipipe_car {int en; scalar_t__ hpf_shft; TYPE_2__ gain2; TYPE_1__ gain1; } ;

/* Variables and functions */
 scalar_t__ CAR_GAIN1_SHFT_MASK ; 
 scalar_t__ CAR_GAIN2_SHFT_MASK ; 
 scalar_t__ CAR_GAIN_MIN_MASK ; 
 scalar_t__ CAR_HPF_SHIFT_MASK ; 
 int EINVAL ; 

__attribute__((used)) static int ipipe_validate_car_params(struct vpfe_ipipe_car *car)
{
	if (car->en > 1 || car->hpf_shft > CAR_HPF_SHIFT_MASK ||
	    car->gain1.shft > CAR_GAIN1_SHFT_MASK ||
	    car->gain1.gain_min > CAR_GAIN_MIN_MASK ||
	    car->gain2.shft > CAR_GAIN2_SHFT_MASK ||
	    car->gain2.gain_min > CAR_GAIN_MIN_MASK)
		return -EINVAL;

	return 0;
}