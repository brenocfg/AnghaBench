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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_REF_FW_DBG_COLLECT ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_fwrt_dump_end(void *ctx)
{
	struct iwl_mvm *mvm = ctx;

	mutex_unlock(&mvm->mutex);

	iwl_mvm_unref(mvm, IWL_MVM_REF_FW_DBG_COLLECT);
}