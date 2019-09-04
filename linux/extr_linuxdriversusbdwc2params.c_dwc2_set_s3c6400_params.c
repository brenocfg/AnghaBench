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
struct dwc2_core_params {scalar_t__ power_down; } ;
struct dwc2_hsotg {struct dwc2_core_params params; } ;

/* Variables and functions */

__attribute__((used)) static void dwc2_set_s3c6400_params(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *p = &hsotg->params;

	p->power_down = 0;
}