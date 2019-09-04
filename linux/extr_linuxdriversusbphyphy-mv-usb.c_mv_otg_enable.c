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
struct mv_otg {scalar_t__ clock_gating; } ;

/* Variables and functions */
 int mv_otg_enable_internal (struct mv_otg*) ; 

__attribute__((used)) static int mv_otg_enable(struct mv_otg *mvotg)
{
	if (mvotg->clock_gating)
		return mv_otg_enable_internal(mvotg);

	return 0;
}