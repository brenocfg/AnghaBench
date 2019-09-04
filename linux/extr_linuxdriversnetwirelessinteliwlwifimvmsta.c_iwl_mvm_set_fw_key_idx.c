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
struct iwl_mvm {int* fw_key_deleted; int /*<<< orphan*/  fw_key_table; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int STA_KEY_IDX_INVALID ; 
 int STA_KEY_MAX_NUM ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_set_fw_key_idx(struct iwl_mvm *mvm)
{
	int i, max = -1, max_offs = -1;

	lockdep_assert_held(&mvm->mutex);

	/* Pick the unused key offset with the highest 'deleted'
	 * counter. Every time a key is deleted, all the counters
	 * are incremented and the one that was just deleted is
	 * reset to zero. Thus, the highest counter is the one
	 * that was deleted longest ago. Pick that one.
	 */
	for (i = 0; i < STA_KEY_MAX_NUM; i++) {
		if (test_bit(i, mvm->fw_key_table))
			continue;
		if (mvm->fw_key_deleted[i] > max) {
			max = mvm->fw_key_deleted[i];
			max_offs = i;
		}
	}

	if (max_offs < 0)
		return STA_KEY_IDX_INVALID;

	return max_offs;
}