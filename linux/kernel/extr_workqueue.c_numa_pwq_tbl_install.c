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
struct workqueue_struct {int /*<<< orphan*/ * numa_pwq_tbl; int /*<<< orphan*/  mutex; } ;
struct pool_workqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_pwq (struct pool_workqueue*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct pool_workqueue* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct pool_workqueue*) ; 
 int /*<<< orphan*/  wq_pool_mutex ; 

__attribute__((used)) static struct pool_workqueue *numa_pwq_tbl_install(struct workqueue_struct *wq,
						   int node,
						   struct pool_workqueue *pwq)
{
	struct pool_workqueue *old_pwq;

	lockdep_assert_held(&wq_pool_mutex);
	lockdep_assert_held(&wq->mutex);

	/* link_pwq() can handle duplicate calls */
	link_pwq(pwq);

	old_pwq = rcu_access_pointer(wq->numa_pwq_tbl[node]);
	rcu_assign_pointer(wq->numa_pwq_tbl[node], pwq);
	return old_pwq;
}