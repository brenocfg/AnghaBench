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
struct TYPE_4__ {int power_down; } ;
struct TYPE_3__ {scalar_t__ power_optimized; scalar_t__ hibernation; } ;
struct dwc2_hsotg {TYPE_2__ params; TYPE_1__ hw_params; } ;

/* Variables and functions */

__attribute__((used)) static void dwc2_set_param_power_down(struct dwc2_hsotg *hsotg)
{
	int val;

	if (hsotg->hw_params.hibernation)
		val = 2;
	else if (hsotg->hw_params.power_optimized)
		val = 1;
	else
		val = 0;

	hsotg->params.power_down = val;
}