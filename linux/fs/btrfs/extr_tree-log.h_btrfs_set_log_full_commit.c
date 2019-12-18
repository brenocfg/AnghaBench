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
struct btrfs_trans_handle {int /*<<< orphan*/  transid; TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_trans_log_full_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_set_log_full_commit(struct btrfs_trans_handle *trans)
{
	WRITE_ONCE(trans->fs_info->last_trans_log_full_commit, trans->transid);
}