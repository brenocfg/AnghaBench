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
typedef  size_t u16 ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  ref; } ;
struct iwl_mvm {struct iwl_mvm_phy_ctxt* phy_ctxts; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 size_t NUM_PHY_CTX ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iwl_mvm_phy_ctxt *iwl_mvm_get_free_phy_ctxt(struct iwl_mvm *mvm)
{
	u16 i;

	lockdep_assert_held(&mvm->mutex);

	for (i = 0; i < NUM_PHY_CTX; i++)
		if (!mvm->phy_ctxts[i].ref)
			return &mvm->phy_ctxts[i];

	IWL_ERR(mvm, "No available PHY context\n");
	return NULL;
}