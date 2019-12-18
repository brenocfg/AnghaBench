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
struct xfs_mount {int /*<<< orphan*/  m_icount; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  XFS_ICOUNT_BATCH ; 
 scalar_t__ __percpu_counter_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_mod_icount(
	struct xfs_mount	*mp,
	int64_t			delta)
{
	percpu_counter_add_batch(&mp->m_icount, delta, XFS_ICOUNT_BATCH);
	if (__percpu_counter_compare(&mp->m_icount, 0, XFS_ICOUNT_BATCH) < 0) {
		ASSERT(0);
		percpu_counter_add(&mp->m_icount, -delta);
		return -EINVAL;
	}
	return 0;
}