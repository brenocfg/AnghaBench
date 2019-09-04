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
struct dwc3_hwparams {int dummy; } ;
struct dwc3 {int /*<<< orphan*/  num_eps; struct dwc3_hwparams hwparams; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_NUM_EPS (struct dwc3_hwparams*) ; 

__attribute__((used)) static void dwc3_core_num_eps(struct dwc3 *dwc)
{
	struct dwc3_hwparams	*parms = &dwc->hwparams;

	dwc->num_eps = DWC3_NUM_EPS(parms);
}