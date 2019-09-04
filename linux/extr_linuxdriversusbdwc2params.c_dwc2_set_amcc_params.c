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
struct dwc2_core_params {int ahbcfg; } ;
struct dwc2_hsotg {struct dwc2_core_params params; } ;

/* Variables and functions */
 int GAHBCFG_HBSTLEN_INCR16 ; 
 int GAHBCFG_HBSTLEN_SHIFT ; 

__attribute__((used)) static void dwc2_set_amcc_params(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *p = &hsotg->params;

	p->ahbcfg = GAHBCFG_HBSTLEN_INCR16 << GAHBCFG_HBSTLEN_SHIFT;
}