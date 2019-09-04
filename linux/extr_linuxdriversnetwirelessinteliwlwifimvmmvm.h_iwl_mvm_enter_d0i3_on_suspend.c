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
struct iwl_mvm {TYPE_1__* trans; } ;
struct TYPE_2__ {scalar_t__ system_pm_mode; scalar_t__ runtime_pm_mode; } ;

/* Variables and functions */
 scalar_t__ IWL_PLAT_PM_MODE_D0I3 ; 

__attribute__((used)) static inline bool iwl_mvm_enter_d0i3_on_suspend(struct iwl_mvm *mvm)
{
	/* For now we only use this mode to differentiate between
	 * slave transports, which handle D0i3 entry in suspend by
	 * themselves in conjunction with runtime PM D0i3.  So, this
	 * function is used to check whether we need to do anything
	 * when entering suspend or if the transport layer has already
	 * done it.
	 */
	return (mvm->trans->system_pm_mode == IWL_PLAT_PM_MODE_D0I3) &&
		(mvm->trans->runtime_pm_mode != IWL_PLAT_PM_MODE_D0I3);
}