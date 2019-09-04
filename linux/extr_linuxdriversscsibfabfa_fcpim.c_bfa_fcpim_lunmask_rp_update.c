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
typedef  scalar_t__ wwn_t ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct bfa_s {int dummy; } ;
struct bfa_lun_mask_s {scalar_t__ state; scalar_t__ lp_wwn; scalar_t__ rp_wwn; size_t lp_tag; int /*<<< orphan*/  rp_tag; } ;

/* Variables and functions */
 scalar_t__ BFA_IOIM_LUN_MASK_ACTIVE ; 
 scalar_t__ BFA_LUNMASK_MINCFG ; 
 size_t MAX_LUN_MASK_CFG ; 
 struct bfa_lun_mask_s* bfa_get_lun_mask_list (struct bfa_s*) ; 
 scalar_t__ bfa_get_lun_mask_status (struct bfa_s*) ; 

void
bfa_fcpim_lunmask_rp_update(struct bfa_s *bfa, wwn_t lp_wwn, wwn_t rp_wwn,
			u16 rp_tag, u8 lp_tag)
{
	struct bfa_lun_mask_s *lun_list;
	u8	i;

	if (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		return;

	lun_list = bfa_get_lun_mask_list(bfa);
	for (i = 0; i < MAX_LUN_MASK_CFG; i++) {
		if (lun_list[i].state == BFA_IOIM_LUN_MASK_ACTIVE) {
			if ((lun_list[i].lp_wwn == lp_wwn) &&
			    (lun_list[i].rp_wwn == rp_wwn)) {
				lun_list[i].rp_tag = rp_tag;
				lun_list[i].lp_tag = lp_tag;
			}
		}
	}
}