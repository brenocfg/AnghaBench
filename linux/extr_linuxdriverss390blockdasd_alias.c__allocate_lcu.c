#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dasd_uid {int /*<<< orphan*/  ssid; int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor; } ;
struct ccw1 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dwork; } ;
struct TYPE_5__ {int /*<<< orphan*/  worker; } ;
struct TYPE_4__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor; } ;
struct alias_lcu {int flags; struct alias_lcu* uac; struct alias_lcu* rsu_cqr; struct alias_lcu* cpaddr; int /*<<< orphan*/  lcu_setup; int /*<<< orphan*/  lock; TYPE_3__ ruac_data; TYPE_2__ suc_data; int /*<<< orphan*/  grouplist; int /*<<< orphan*/  active_devices; int /*<<< orphan*/  inactive_devices; int /*<<< orphan*/  lcu; int /*<<< orphan*/  pav; TYPE_1__ uid; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct alias_lcu* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NEED_UAC_UPDATE ; 
 int /*<<< orphan*/  NO_PAV ; 
 int UPDATE_PENDING ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct alias_lcu*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  lcu_update_work ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  summary_unit_check_handling_work ; 

__attribute__((used)) static struct alias_lcu *_allocate_lcu(struct dasd_uid *uid)
{
	struct alias_lcu *lcu;

	lcu = kzalloc(sizeof(*lcu), GFP_KERNEL);
	if (!lcu)
		return ERR_PTR(-ENOMEM);
	lcu->uac = kzalloc(sizeof(*(lcu->uac)), GFP_KERNEL | GFP_DMA);
	if (!lcu->uac)
		goto out_err1;
	lcu->rsu_cqr = kzalloc(sizeof(*lcu->rsu_cqr), GFP_KERNEL | GFP_DMA);
	if (!lcu->rsu_cqr)
		goto out_err2;
	lcu->rsu_cqr->cpaddr = kzalloc(sizeof(struct ccw1),
				       GFP_KERNEL | GFP_DMA);
	if (!lcu->rsu_cqr->cpaddr)
		goto out_err3;
	lcu->rsu_cqr->data = kzalloc(16, GFP_KERNEL | GFP_DMA);
	if (!lcu->rsu_cqr->data)
		goto out_err4;

	memcpy(lcu->uid.vendor, uid->vendor, sizeof(uid->vendor));
	memcpy(lcu->uid.serial, uid->serial, sizeof(uid->serial));
	lcu->uid.ssid = uid->ssid;
	lcu->pav = NO_PAV;
	lcu->flags = NEED_UAC_UPDATE | UPDATE_PENDING;
	INIT_LIST_HEAD(&lcu->lcu);
	INIT_LIST_HEAD(&lcu->inactive_devices);
	INIT_LIST_HEAD(&lcu->active_devices);
	INIT_LIST_HEAD(&lcu->grouplist);
	INIT_WORK(&lcu->suc_data.worker, summary_unit_check_handling_work);
	INIT_DELAYED_WORK(&lcu->ruac_data.dwork, lcu_update_work);
	spin_lock_init(&lcu->lock);
	init_completion(&lcu->lcu_setup);
	return lcu;

out_err4:
	kfree(lcu->rsu_cqr->cpaddr);
out_err3:
	kfree(lcu->rsu_cqr);
out_err2:
	kfree(lcu->uac);
out_err1:
	kfree(lcu);
	return ERR_PTR(-ENOMEM);
}