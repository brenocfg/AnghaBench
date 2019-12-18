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
struct rdmacg_resource_pool {int /*<<< orphan*/  dev_node; int /*<<< orphan*/  cg_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rdmacg_resource_pool*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmacg_mutex ; 

__attribute__((used)) static void free_cg_rpool_locked(struct rdmacg_resource_pool *rpool)
{
	lockdep_assert_held(&rdmacg_mutex);

	list_del(&rpool->cg_node);
	list_del(&rpool->dev_node);
	kfree(rpool);
}