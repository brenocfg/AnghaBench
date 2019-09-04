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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_space_info {scalar_t__ bytes_may_use; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct btrfs_fs_info {struct btrfs_space_info* data_sinfo; int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 scalar_t__ round_down (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ round_up (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void btrfs_free_reserved_data_space_noquota(struct inode *inode, u64 start,
					    u64 len)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_space_info *data_sinfo;

	/* Make sure the range is aligned to sectorsize */
	len = round_up(start + len, fs_info->sectorsize) -
	      round_down(start, fs_info->sectorsize);
	start = round_down(start, fs_info->sectorsize);

	data_sinfo = fs_info->data_sinfo;
	spin_lock(&data_sinfo->lock);
	if (WARN_ON(data_sinfo->bytes_may_use < len))
		data_sinfo->bytes_may_use = 0;
	else
		data_sinfo->bytes_may_use -= len;
	trace_btrfs_space_reservation(fs_info, "space_info",
				      data_sinfo->flags, len, 0);
	spin_unlock(&data_sinfo->lock);
}