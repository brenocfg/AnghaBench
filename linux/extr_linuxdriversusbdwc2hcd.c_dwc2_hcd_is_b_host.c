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
struct dwc2_hsotg {scalar_t__ op_state; } ;

/* Variables and functions */
 scalar_t__ OTG_STATE_B_HOST ; 

int dwc2_hcd_is_b_host(struct dwc2_hsotg *hsotg)
{
	return hsotg->op_state == OTG_STATE_B_HOST;
}