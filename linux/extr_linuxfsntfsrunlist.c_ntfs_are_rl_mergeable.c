#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lcn; scalar_t__ vcn; scalar_t__ length; } ;
typedef  TYPE_1__ runlist_element ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ LCN_HOLE ; 
 scalar_t__ LCN_RL_NOT_MAPPED ; 

__attribute__((used)) static inline bool ntfs_are_rl_mergeable(runlist_element *dst,
		runlist_element *src)
{
	BUG_ON(!dst);
	BUG_ON(!src);

	/* We can merge unmapped regions even if they are misaligned. */
	if ((dst->lcn == LCN_RL_NOT_MAPPED) && (src->lcn == LCN_RL_NOT_MAPPED))
		return true;
	/* If the runs are misaligned, we cannot merge them. */
	if ((dst->vcn + dst->length) != src->vcn)
		return false;
	/* If both runs are non-sparse and contiguous, we can merge them. */
	if ((dst->lcn >= 0) && (src->lcn >= 0) &&
			((dst->lcn + dst->length) == src->lcn))
		return true;
	/* If we are merging two holes, we can merge them. */
	if ((dst->lcn == LCN_HOLE) && (src->lcn == LCN_HOLE))
		return true;
	/* Cannot merge. */
	return false;
}