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
struct kernfs_node {int /*<<< orphan*/  dep_map; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  atomic_inc_unless_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ kernfs_lockdep (struct kernfs_node*) ; 
 int /*<<< orphan*/  rwsem_acquire_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct kernfs_node *kernfs_get_active(struct kernfs_node *kn)
{
	if (unlikely(!kn))
		return NULL;

	if (!atomic_inc_unless_negative(&kn->active))
		return NULL;

	if (kernfs_lockdep(kn))
		rwsem_acquire_read(&kn->dep_map, 0, 1, _RET_IP_);
	return kn;
}