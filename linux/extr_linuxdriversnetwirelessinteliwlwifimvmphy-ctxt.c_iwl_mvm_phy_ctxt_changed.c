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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  width; TYPE_2__* channel; } ;
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  mutex; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  width; TYPE_2__* chan; } ;
typedef  enum iwl_ctxt_action { ____Placeholder_iwl_ctxt_action } iwl_ctxt_action ;
struct TYPE_4__ {scalar_t__ band; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int FW_CTXT_ACTION_ADD ; 
 int FW_CTXT_ACTION_MODIFY ; 
 int FW_CTXT_ACTION_REMOVE ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_BINDING_CDB_SUPPORT ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_phy_ctxt_apply (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,struct cfg80211_chan_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_phy_ctxt_changed(struct iwl_mvm *mvm, struct iwl_mvm_phy_ctxt *ctxt,
			     struct cfg80211_chan_def *chandef,
			     u8 chains_static, u8 chains_dynamic)
{
	enum iwl_ctxt_action action = FW_CTXT_ACTION_MODIFY;

	lockdep_assert_held(&mvm->mutex);

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_BINDING_CDB_SUPPORT) &&
	    ctxt->channel->band != chandef->chan->band) {
		int ret;

		/* ... remove it here ...*/
		ret = iwl_mvm_phy_ctxt_apply(mvm, ctxt, chandef,
					     chains_static, chains_dynamic,
					     FW_CTXT_ACTION_REMOVE, 0);
		if (ret)
			return ret;

		/* ... and proceed to add it again */
		action = FW_CTXT_ACTION_ADD;
	}

	ctxt->channel = chandef->chan;
	ctxt->width = chandef->width;
	return iwl_mvm_phy_ctxt_apply(mvm, ctxt, chandef,
				      chains_static, chains_dynamic,
				      action, 0);
}