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
struct btrfs_trans_handle {int transid; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  type; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __TRANS_DUMMY ; 
 int /*<<< orphan*/  memset (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int) ; 

void btrfs_init_dummy_trans(struct btrfs_trans_handle *trans,
			    struct btrfs_fs_info *fs_info)
{
	memset(trans, 0, sizeof(*trans));
	trans->transid = 1;
	trans->type = __TRANS_DUMMY;
	trans->fs_info = fs_info;
}