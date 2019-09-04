#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum ufs_pm_level { ____Placeholder_ufs_pm_level } ufs_pm_level ;
typedef  enum ufs_dev_pwr_mode { ____Placeholder_ufs_dev_pwr_mode } ufs_dev_pwr_mode ;
struct TYPE_2__ {int dev_state; } ;

/* Variables and functions */
 TYPE_1__* ufs_pm_lvl_states ; 

__attribute__((used)) static inline enum ufs_dev_pwr_mode
ufs_get_pm_lvl_to_dev_pwr_mode(enum ufs_pm_level lvl)
{
	return ufs_pm_lvl_states[lvl].dev_state;
}