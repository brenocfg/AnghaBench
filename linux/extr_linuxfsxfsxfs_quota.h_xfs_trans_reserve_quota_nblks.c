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
typedef  int /*<<< orphan*/  uint ;
struct xfs_trans {int dummy; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int xfs_trans_reserve_quota_nblks(struct xfs_trans *tp,
		struct xfs_inode *ip, long nblks, long ninos, uint flags)
{
	return 0;
}