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
struct dentry {int /*<<< orphan*/  d_lock; } ;
struct TYPE_2__ {scalar_t__ lease_shared_gen; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 TYPE_1__* ceph_dentry (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_invalidate_dentry_lease(struct dentry *dentry)
{
	spin_lock(&dentry->d_lock);
	ceph_dentry(dentry)->time = jiffies;
	ceph_dentry(dentry)->lease_shared_gen = 0;
	spin_unlock(&dentry->d_lock);
}