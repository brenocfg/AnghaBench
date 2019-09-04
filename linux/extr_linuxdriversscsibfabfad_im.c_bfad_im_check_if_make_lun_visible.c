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
typedef  scalar_t__ u8 ;
struct scsi_device {scalar_t__ lun; } ;
struct fc_rport {scalar_t__ dd_data; } ;
struct bfad_itnim_data_s {TYPE_2__* itnim; } ;
struct bfa_s {int dummy; } ;
struct TYPE_6__ {scalar_t__ lp_tag; } ;
struct bfa_rport_s {scalar_t__ rport_tag; TYPE_3__ rport_info; } ;
struct bfa_lun_mask_s {scalar_t__ state; scalar_t__ rp_tag; scalar_t__ lp_tag; int /*<<< orphan*/  lun; } ;
struct TYPE_5__ {TYPE_1__* bfa_itnim; } ;
struct TYPE_4__ {struct bfa_rport_s* rport; struct bfa_s* bfa; } ;

/* Variables and functions */
 scalar_t__ BFA_IOIM_LUN_MASK_ACTIVE ; 
 int BFA_STATUS_OK ; 
 int ENXIO ; 
 int MAX_LUN_MASK_CFG ; 
 struct bfa_lun_mask_s* bfa_get_lun_mask_list (struct bfa_s*) ; 
 scalar_t__ scsilun_to_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bfad_im_check_if_make_lun_visible(struct scsi_device *sdev,
				  struct fc_rport *rport)
{
	struct bfad_itnim_data_s *itnim_data =
				(struct bfad_itnim_data_s *) rport->dd_data;
	struct bfa_s *bfa = itnim_data->itnim->bfa_itnim->bfa;
	struct bfa_rport_s *bfa_rport = itnim_data->itnim->bfa_itnim->rport;
	struct bfa_lun_mask_s *lun_list = bfa_get_lun_mask_list(bfa);
	int i = 0, ret = -ENXIO;

	for (i = 0; i < MAX_LUN_MASK_CFG; i++) {
		if (lun_list[i].state == BFA_IOIM_LUN_MASK_ACTIVE &&
		    scsilun_to_int(&lun_list[i].lun) == sdev->lun &&
		    lun_list[i].rp_tag == bfa_rport->rport_tag &&
		    lun_list[i].lp_tag == (u8)bfa_rport->rport_info.lp_tag) {
			ret = BFA_STATUS_OK;
			break;
		}
	}
	return ret;
}