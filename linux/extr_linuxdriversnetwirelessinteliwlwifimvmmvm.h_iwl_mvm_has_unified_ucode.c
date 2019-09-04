#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm {TYPE_2__* trans; } ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {scalar_t__ device_family; } ;

/* Variables and functions */
 scalar_t__ IWL_DEVICE_FAMILY_22000 ; 

__attribute__((used)) static inline bool iwl_mvm_has_unified_ucode(struct iwl_mvm *mvm)
{
	/* TODO - better define this */
	return mvm->trans->cfg->device_family >= IWL_DEVICE_FAMILY_22000;
}