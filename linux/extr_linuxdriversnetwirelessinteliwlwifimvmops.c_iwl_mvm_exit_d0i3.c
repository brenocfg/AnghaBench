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
struct iwl_op_mode {int dummy; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_REF_EXIT_WORK ; 
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int _iwl_mvm_exit_d0i3 (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_ref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 

int iwl_mvm_exit_d0i3(struct iwl_op_mode *op_mode)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);

	iwl_mvm_ref(mvm, IWL_MVM_REF_EXIT_WORK);
	return _iwl_mvm_exit_d0i3(mvm);
}