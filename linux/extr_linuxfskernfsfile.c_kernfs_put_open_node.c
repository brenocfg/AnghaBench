#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kernfs_open_node {int /*<<< orphan*/  refcnt; } ;
struct kernfs_open_file {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct kernfs_open_node* open; } ;
struct kernfs_node {TYPE_1__ attr; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_open_file_mutex ; 
 int /*<<< orphan*/  kernfs_open_node_lock ; 
 int /*<<< orphan*/  kfree (struct kernfs_open_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kernfs_put_open_node(struct kernfs_node *kn,
				 struct kernfs_open_file *of)
{
	struct kernfs_open_node *on = kn->attr.open;
	unsigned long flags;

	mutex_lock(&kernfs_open_file_mutex);
	spin_lock_irqsave(&kernfs_open_node_lock, flags);

	if (of)
		list_del(&of->list);

	if (atomic_dec_and_test(&on->refcnt))
		kn->attr.open = NULL;
	else
		on = NULL;

	spin_unlock_irqrestore(&kernfs_open_node_lock, flags);
	mutex_unlock(&kernfs_open_file_mutex);

	kfree(on);
}