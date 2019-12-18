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
struct TYPE_2__ {int /*<<< orphan*/  d_blk_hardlimit; } ;
struct xfs_dquot {scalar_t__ q_res_bcount; scalar_t__* q_low_space; TYPE_1__ q_core; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 size_t XFS_QLOWSP_1_PCNT ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool xfs_dquot_lowsp(struct xfs_dquot *dqp)
{
	int64_t freesp;

	freesp = be64_to_cpu(dqp->q_core.d_blk_hardlimit) - dqp->q_res_bcount;
	if (freesp < dqp->q_low_space[XFS_QLOWSP_1_PCNT])
		return true;

	return false;
}