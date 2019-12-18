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
struct worker_pool {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WORK_OFFQ_POOL_NONE ; 
 int idr_alloc (int /*<<< orphan*/ *,struct worker_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_pool_idr ; 
 int /*<<< orphan*/  wq_pool_mutex ; 

__attribute__((used)) static int worker_pool_assign_id(struct worker_pool *pool)
{
	int ret;

	lockdep_assert_held(&wq_pool_mutex);

	ret = idr_alloc(&worker_pool_idr, pool, 0, WORK_OFFQ_POOL_NONE,
			GFP_KERNEL);
	if (ret >= 0) {
		pool->id = ret;
		return 0;
	}
	return ret;
}