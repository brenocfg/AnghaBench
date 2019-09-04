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
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_object_rcu ; 

__attribute__((used)) static void put_object(struct kmemleak_object *object)
{
	if (!atomic_dec_and_test(&object->use_count))
		return;

	/* should only get here after delete_object was called */
	WARN_ON(object->flags & OBJECT_ALLOCATED);

	call_rcu(&object->rcu, free_object_rcu);
}