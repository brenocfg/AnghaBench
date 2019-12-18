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
struct send_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 int get_cur_inode_state (struct send_ctx*,scalar_t__,scalar_t__) ; 
 int inode_state_did_create ; 
 int inode_state_no_change ; 
 int inode_state_will_delete ; 

__attribute__((used)) static int is_inode_existent(struct send_ctx *sctx, u64 ino, u64 gen)
{
	int ret;

	if (ino == BTRFS_FIRST_FREE_OBJECTID)
		return 1;

	ret = get_cur_inode_state(sctx, ino, gen);
	if (ret < 0)
		goto out;

	if (ret == inode_state_no_change ||
	    ret == inode_state_did_create ||
	    ret == inode_state_will_delete)
		ret = 1;
	else
		ret = 0;

out:
	return ret;
}