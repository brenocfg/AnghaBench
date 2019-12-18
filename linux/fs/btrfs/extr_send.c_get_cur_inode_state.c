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
struct send_ctx {scalar_t__ send_progress; int /*<<< orphan*/  parent_root; int /*<<< orphan*/  send_root; } ;

/* Variables and functions */
 int ENOENT ; 
 int get_inode_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int inode_state_did_create ; 
 int inode_state_did_delete ; 
 int inode_state_no_change ; 
 int inode_state_will_create ; 
 int inode_state_will_delete ; 

__attribute__((used)) static int get_cur_inode_state(struct send_ctx *sctx, u64 ino, u64 gen)
{
	int ret;
	int left_ret;
	int right_ret;
	u64 left_gen;
	u64 right_gen;

	ret = get_inode_info(sctx->send_root, ino, NULL, &left_gen, NULL, NULL,
			NULL, NULL);
	if (ret < 0 && ret != -ENOENT)
		goto out;
	left_ret = ret;

	if (!sctx->parent_root) {
		right_ret = -ENOENT;
	} else {
		ret = get_inode_info(sctx->parent_root, ino, NULL, &right_gen,
				NULL, NULL, NULL, NULL);
		if (ret < 0 && ret != -ENOENT)
			goto out;
		right_ret = ret;
	}

	if (!left_ret && !right_ret) {
		if (left_gen == gen && right_gen == gen) {
			ret = inode_state_no_change;
		} else if (left_gen == gen) {
			if (ino < sctx->send_progress)
				ret = inode_state_did_create;
			else
				ret = inode_state_will_create;
		} else if (right_gen == gen) {
			if (ino < sctx->send_progress)
				ret = inode_state_did_delete;
			else
				ret = inode_state_will_delete;
		} else  {
			ret = -ENOENT;
		}
	} else if (!left_ret) {
		if (left_gen == gen) {
			if (ino < sctx->send_progress)
				ret = inode_state_did_create;
			else
				ret = inode_state_will_create;
		} else {
			ret = -ENOENT;
		}
	} else if (!right_ret) {
		if (right_gen == gen) {
			if (ino < sctx->send_progress)
				ret = inode_state_did_delete;
			else
				ret = inode_state_will_delete;
		} else {
			ret = -ENOENT;
		}
	} else {
		ret = -ENOENT;
	}

out:
	return ret;
}