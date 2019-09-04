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
 int /*<<< orphan*/  do_nhm_platform_info ; 
 int /*<<< orphan*/  dump_atom_turbo_ratio_limits () ; 
 int /*<<< orphan*/  dump_config_tdp () ; 
 int /*<<< orphan*/  dump_hsw_turbo_ratio_limits () ; 
 int /*<<< orphan*/  dump_ivt_turbo_ratio_limits () ; 
 int /*<<< orphan*/  dump_knl_turbo_ratio_limits () ; 
 int /*<<< orphan*/  dump_nhm_cst_cfg () ; 
 int /*<<< orphan*/  dump_nhm_platform_info () ; 
 int /*<<< orphan*/  dump_turbo_ratio_limits (unsigned int,unsigned int) ; 
 scalar_t__ has_atom_turbo_ratio_limit (unsigned int,unsigned int) ; 
 scalar_t__ has_config_tdp (unsigned int,unsigned int) ; 
 scalar_t__ has_hsw_turbo_ratio_limit (unsigned int,unsigned int) ; 
 scalar_t__ has_ivt_turbo_ratio_limit (unsigned int,unsigned int) ; 
 scalar_t__ has_knl_turbo_ratio_limit (unsigned int,unsigned int) ; 
 scalar_t__ has_turbo_ratio_limit (unsigned int,unsigned int) ; 

__attribute__((used)) static void
dump_cstate_pstate_config_info(unsigned int family, unsigned int model)
{
	if (!do_nhm_platform_info)
		return;

	dump_nhm_platform_info();

	if (has_hsw_turbo_ratio_limit(family, model))
		dump_hsw_turbo_ratio_limits();

	if (has_ivt_turbo_ratio_limit(family, model))
		dump_ivt_turbo_ratio_limits();

	if (has_turbo_ratio_limit(family, model))
		dump_turbo_ratio_limits(family, model);

	if (has_atom_turbo_ratio_limit(family, model))
		dump_atom_turbo_ratio_limits();

	if (has_knl_turbo_ratio_limit(family, model))
		dump_knl_turbo_ratio_limits();

	if (has_config_tdp(family, model))
		dump_config_tdp();

	dump_nhm_cst_cfg();
}