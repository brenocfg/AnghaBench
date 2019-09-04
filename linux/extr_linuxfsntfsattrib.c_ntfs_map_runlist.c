#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  rl; } ;
struct TYPE_6__ {TYPE_1__ runlist; } ;
typedef  TYPE_2__ ntfs_inode ;
typedef  int /*<<< orphan*/  VCN ;

/* Variables and functions */
 scalar_t__ LCN_RL_NOT_MAPPED ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int ntfs_map_runlist_nolock (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ntfs_rl_vcn_to_lcn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ntfs_map_runlist(ntfs_inode *ni, VCN vcn)
{
	int err = 0;

	down_write(&ni->runlist.lock);
	/* Make sure someone else didn't do the work while we were sleeping. */
	if (likely(ntfs_rl_vcn_to_lcn(ni->runlist.rl, vcn) <=
			LCN_RL_NOT_MAPPED))
		err = ntfs_map_runlist_nolock(ni, vcn, NULL);
	up_write(&ni->runlist.lock);
	return err;
}