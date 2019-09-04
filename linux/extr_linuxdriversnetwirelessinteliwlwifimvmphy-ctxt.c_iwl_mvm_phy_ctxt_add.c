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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  channel; scalar_t__ ref; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CTXT_ACTION_ADD ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int iwl_mvm_phy_ctxt_apply (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,struct cfg80211_chan_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_mvm_phy_ctxt_add(struct iwl_mvm *mvm, struct iwl_mvm_phy_ctxt *ctxt,
			 struct cfg80211_chan_def *chandef,
			 u8 chains_static, u8 chains_dynamic)
{
	WARN_ON(!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		ctxt->ref);
	lockdep_assert_held(&mvm->mutex);

	ctxt->channel = chandef->chan;

	return iwl_mvm_phy_ctxt_apply(mvm, ctxt, chandef,
				      chains_static, chains_dynamic,
				      FW_CTXT_ACTION_ADD, 0);
}