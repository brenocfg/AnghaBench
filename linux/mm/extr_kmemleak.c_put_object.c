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
struct kmemleak_object {int flags; int /*<<< orphan*/  rcu; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int OBJECT_ALLOCATED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  free_object_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ object_cache ; 

__attribute__((used)) static void put_object(struct kmemleak_object *object)
{
	if (!atomic_dec_and_test(&object->use_count))
		return;

	/* should only get here after delete_object was called */
	WARN_ON(object->flags & OBJECT_ALLOCATED);

	/*
	 * It may be too early for the RCU callbacks, however, there is no
	 * concurrent object_list traversal when !object_cache and all objects
	 * came from the memory pool. Free the object directly.
	 */
	if (object_cache)
		call_rcu(&object->rcu, free_object_rcu);
	else
		free_object_rcu(&object->rcu);
}