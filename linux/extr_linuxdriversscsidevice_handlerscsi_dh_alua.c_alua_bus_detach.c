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
struct scsi_device {struct alua_dh_data* handler_data; } ;
struct alua_port_group {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; } ;
struct alua_dh_data {int /*<<< orphan*/  node; int /*<<< orphan*/  pg_lock; int /*<<< orphan*/ * sdev; int /*<<< orphan*/  pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct alua_dh_data*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct alua_port_group* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_port_group ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alua_bus_detach(struct scsi_device *sdev)
{
	struct alua_dh_data *h = sdev->handler_data;
	struct alua_port_group *pg;

	spin_lock(&h->pg_lock);
	pg = rcu_dereference_protected(h->pg, lockdep_is_held(&h->pg_lock));
	rcu_assign_pointer(h->pg, NULL);
	h->sdev = NULL;
	spin_unlock(&h->pg_lock);
	if (pg) {
		spin_lock_irq(&pg->lock);
		list_del_rcu(&h->node);
		spin_unlock_irq(&pg->lock);
		kref_put(&pg->kref, release_port_group);
	}
	sdev->handler_data = NULL;
	kfree(h);
}