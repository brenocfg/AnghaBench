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
typedef  int /*<<< orphan*/  uint32_t ;
struct dlm_ls {int /*<<< orphan*/  ls_lkbidr_spin; int /*<<< orphan*/  ls_lkbidr; } ;
struct dlm_lkb {scalar_t__ lkb_lvbptr; int /*<<< orphan*/  lkb_ref; int /*<<< orphan*/  lkb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  dlm_free_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  dlm_free_lvb (scalar_t__) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_master_copy (struct dlm_lkb*) ; 
 int /*<<< orphan*/  kill_lkb ; 
 scalar_t__ kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __put_lkb(struct dlm_ls *ls, struct dlm_lkb *lkb)
{
	uint32_t lkid = lkb->lkb_id;

	spin_lock(&ls->ls_lkbidr_spin);
	if (kref_put(&lkb->lkb_ref, kill_lkb)) {
		idr_remove(&ls->ls_lkbidr, lkid);
		spin_unlock(&ls->ls_lkbidr_spin);

		detach_lkb(lkb);

		/* for local/process lkbs, lvbptr points to caller's lksb */
		if (lkb->lkb_lvbptr && is_master_copy(lkb))
			dlm_free_lvb(lkb->lkb_lvbptr);
		dlm_free_lkb(lkb);
		return 1;
	} else {
		spin_unlock(&ls->ls_lkbidr_spin);
		return 0;
	}
}