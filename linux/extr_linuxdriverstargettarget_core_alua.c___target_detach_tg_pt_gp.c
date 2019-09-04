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
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_lock; int /*<<< orphan*/  tg_pt_gp_members; } ;
struct se_lun {int /*<<< orphan*/ * lun_tg_pt_gp; int /*<<< orphan*/  lun_tg_pt_gp_link; int /*<<< orphan*/  lun_tg_pt_gp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __target_detach_tg_pt_gp(struct se_lun *lun,
		struct t10_alua_tg_pt_gp *tg_pt_gp)
{
	assert_spin_locked(&lun->lun_tg_pt_gp_lock);

	spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	list_del_init(&lun->lun_tg_pt_gp_link);
	tg_pt_gp->tg_pt_gp_members--;
	spin_unlock(&tg_pt_gp->tg_pt_gp_lock);

	lun->lun_tg_pt_gp = NULL;
}