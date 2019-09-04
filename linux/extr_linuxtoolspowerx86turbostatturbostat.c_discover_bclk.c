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

/* Variables and functions */
 scalar_t__ has_snb_msrs (unsigned int,unsigned int) ; 
 scalar_t__ is_knl (unsigned int,unsigned int) ; 
 scalar_t__ is_slm (unsigned int,unsigned int) ; 
 double slm_bclk () ; 

double discover_bclk(unsigned int family, unsigned int model)
{
	if (has_snb_msrs(family, model) || is_knl(family, model))
		return 100.00;
	else if (is_slm(family, model))
		return slm_bclk();
	else
		return 133.33;
}