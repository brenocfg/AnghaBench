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
struct z3fold_pool {int /*<<< orphan*/  compact_wq; int /*<<< orphan*/  release_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct z3fold_pool*) ; 

__attribute__((used)) static void z3fold_destroy_pool(struct z3fold_pool *pool)
{
	destroy_workqueue(pool->release_wq);
	destroy_workqueue(pool->compact_wq);
	kfree(pool);
}