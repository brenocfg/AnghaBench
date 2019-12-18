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
struct kernfs_node {struct kernfs_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_rename_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct kernfs_node *kernfs_get_parent(struct kernfs_node *kn)
{
	struct kernfs_node *parent;
	unsigned long flags;

	spin_lock_irqsave(&kernfs_rename_lock, flags);
	parent = kn->parent;
	kernfs_get(parent);
	spin_unlock_irqrestore(&kernfs_rename_lock, flags);

	return parent;
}