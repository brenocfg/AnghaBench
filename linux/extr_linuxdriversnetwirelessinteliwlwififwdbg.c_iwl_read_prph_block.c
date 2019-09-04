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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_trans {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  _iwl_read_prph_block (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_trans_grab_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 

__attribute__((used)) static bool iwl_read_prph_block(struct iwl_trans *trans, u32 start,
				u32 len_bytes, __le32 *data)
{
	unsigned long flags;
	bool success = false;

	if (iwl_trans_grab_nic_access(trans, &flags)) {
		success = true;
		_iwl_read_prph_block(trans, start, len_bytes, data);
		iwl_trans_release_nic_access(trans, &flags);
	}

	return success;
}