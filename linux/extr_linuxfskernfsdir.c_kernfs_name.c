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
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int kernfs_name_locked (struct kernfs_node*,char*,size_t) ; 
 int /*<<< orphan*/  kernfs_rename_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int kernfs_name(struct kernfs_node *kn, char *buf, size_t buflen)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&kernfs_rename_lock, flags);
	ret = kernfs_name_locked(kn, buf, buflen);
	spin_unlock_irqrestore(&kernfs_rename_lock, flags);
	return ret;
}