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
struct lm_lockstruct {int ls_recover_size; int /*<<< orphan*/  ls_recover_spin; scalar_t__ ls_recover_block; scalar_t__* ls_recover_submit; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;
struct dlm_slot {int slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdlm_recover_slot(void *arg, struct dlm_slot *slot)
{
	struct gfs2_sbd *sdp = arg;
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	int jid = slot->slot - 1;

	spin_lock(&ls->ls_recover_spin);
	if (ls->ls_recover_size < jid + 1) {
		fs_err(sdp, "recover_slot jid %d gen %u short size %d\n",
		       jid, ls->ls_recover_block, ls->ls_recover_size);
		spin_unlock(&ls->ls_recover_spin);
		return;
	}

	if (ls->ls_recover_submit[jid]) {
		fs_info(sdp, "recover_slot jid %d gen %u prev %u\n",
			jid, ls->ls_recover_block, ls->ls_recover_submit[jid]);
	}
	ls->ls_recover_submit[jid] = ls->ls_recover_block;
	spin_unlock(&ls->ls_recover_spin);
}