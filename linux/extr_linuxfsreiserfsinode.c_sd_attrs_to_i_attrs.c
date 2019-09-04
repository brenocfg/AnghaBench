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
struct inode {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_sb; } ;
typedef  int __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int REISERFS_APPEND_FL ; 
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int REISERFS_IMMUTABLE_FL ; 
 int REISERFS_NOATIME_FL ; 
 int REISERFS_NOTAIL_FL ; 
 int REISERFS_SYNC_FL ; 
 int /*<<< orphan*/  S_APPEND ; 
 int /*<<< orphan*/  S_IMMUTABLE ; 
 int /*<<< orphan*/  S_NOATIME ; 
 int /*<<< orphan*/  S_SYNC ; 
 int /*<<< orphan*/  i_nopack_mask ; 
 scalar_t__ reiserfs_attrs (int /*<<< orphan*/ ) ; 

void sd_attrs_to_i_attrs(__u16 sd_attrs, struct inode *inode)
{
	if (reiserfs_attrs(inode->i_sb)) {
		if (sd_attrs & REISERFS_SYNC_FL)
			inode->i_flags |= S_SYNC;
		else
			inode->i_flags &= ~S_SYNC;
		if (sd_attrs & REISERFS_IMMUTABLE_FL)
			inode->i_flags |= S_IMMUTABLE;
		else
			inode->i_flags &= ~S_IMMUTABLE;
		if (sd_attrs & REISERFS_APPEND_FL)
			inode->i_flags |= S_APPEND;
		else
			inode->i_flags &= ~S_APPEND;
		if (sd_attrs & REISERFS_NOATIME_FL)
			inode->i_flags |= S_NOATIME;
		else
			inode->i_flags &= ~S_NOATIME;
		if (sd_attrs & REISERFS_NOTAIL_FL)
			REISERFS_I(inode)->i_flags |= i_nopack_mask;
		else
			REISERFS_I(inode)->i_flags &= ~i_nopack_mask;
	}
}