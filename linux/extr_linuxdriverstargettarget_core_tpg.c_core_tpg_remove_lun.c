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
struct se_portal_group {int /*<<< orphan*/  tpg_lun_mutex; } ;
struct se_lun {int lun_shutdown; int /*<<< orphan*/  lun_ref; int /*<<< orphan*/  link; scalar_t__ lun_se_dev; int /*<<< orphan*/  lun_dev_link; } ;
struct se_device {TYPE_1__* se_hba; int /*<<< orphan*/  se_port_lock; int /*<<< orphan*/  export_count; } ;
struct TYPE_2__ {int hba_flags; } ;

/* Variables and functions */
 int HBA_FLAGS_INTERNAL_USE ; 
 int /*<<< orphan*/  core_clear_lun_from_tpg (struct se_lun*,struct se_portal_group*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,int /*<<< orphan*/ *) ; 
 struct se_device* rcu_dereference_raw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_detach_tg_pt_gp (struct se_lun*) ; 
 int /*<<< orphan*/  transport_clear_lun_ref (struct se_lun*) ; 

void core_tpg_remove_lun(
	struct se_portal_group *tpg,
	struct se_lun *lun)
{
	/*
	 * rcu_dereference_raw protected by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	struct se_device *dev = rcu_dereference_raw(lun->lun_se_dev);

	lun->lun_shutdown = true;

	core_clear_lun_from_tpg(lun, tpg);
	/*
	 * Wait for any active I/O references to percpu se_lun->lun_ref to
	 * be released.  Also, se_lun->lun_ref is now used by PR and ALUA
	 * logic when referencing a remote target port during ALL_TGT_PT=1
	 * and generating UNIT_ATTENTIONs for ALUA access state transition.
	 */
	transport_clear_lun_ref(lun);

	mutex_lock(&tpg->tpg_lun_mutex);
	if (lun->lun_se_dev) {
		target_detach_tg_pt_gp(lun);

		spin_lock(&dev->se_port_lock);
		list_del(&lun->lun_dev_link);
		dev->export_count--;
		rcu_assign_pointer(lun->lun_se_dev, NULL);
		spin_unlock(&dev->se_port_lock);
	}
	if (!(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		hlist_del_rcu(&lun->link);

	lun->lun_shutdown = false;
	mutex_unlock(&tpg->tpg_lun_mutex);

	percpu_ref_exit(&lun->lun_ref);
}