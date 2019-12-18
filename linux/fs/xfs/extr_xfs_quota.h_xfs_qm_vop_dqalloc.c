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
typedef  int /*<<< orphan*/  xfs_dqid_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_inode {int dummy; } ;
struct xfs_dquot {int dummy; } ;
typedef  int /*<<< orphan*/  prid_t ;

/* Variables and functions */

__attribute__((used)) static inline int
xfs_qm_vop_dqalloc(struct xfs_inode *ip, xfs_dqid_t uid, xfs_dqid_t gid,
		prid_t prid, uint flags, struct xfs_dquot **udqp,
		struct xfs_dquot **gdqp, struct xfs_dquot **pdqp)
{
	*udqp = NULL;
	*gdqp = NULL;
	*pdqp = NULL;
	return 0;
}