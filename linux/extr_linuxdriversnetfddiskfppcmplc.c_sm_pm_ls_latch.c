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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 

void sm_pm_ls_latch(struct s_smc *smc, int phy, int on_off)
/* int on_off;	en- or disable ident. ls */
{
	SK_UNUSED(smc) ;

	phy = phy ; on_off = on_off ;
}