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
struct xfs_mount {int /*<<< orphan*/  m_ifree; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ percpu_counter_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_mod_ifree(
	struct xfs_mount	*mp,
	int64_t			delta)
{
	percpu_counter_add(&mp->m_ifree, delta);
	if (percpu_counter_compare(&mp->m_ifree, 0) < 0) {
		ASSERT(0);
		percpu_counter_add(&mp->m_ifree, -delta);
		return -EINVAL;
	}
	return 0;
}