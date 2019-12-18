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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_MAX_TRANS_DATA ; 
 scalar_t__ ext4_handle_has_enough_credits (int /*<<< orphan*/ *,int) ; 
 int ext4_journal_extend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ext4_journal_restart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int extend_or_restart_transaction(handle_t *handle, int thresh)
{
	int err;

	if (ext4_handle_has_enough_credits(handle, thresh))
		return 0;

	err = ext4_journal_extend(handle, EXT4_MAX_TRANS_DATA);
	if (err < 0)
		return err;
	if (err) {
		err = ext4_journal_restart(handle, EXT4_MAX_TRANS_DATA);
		if (err)
			return err;
	}

	return 0;
}