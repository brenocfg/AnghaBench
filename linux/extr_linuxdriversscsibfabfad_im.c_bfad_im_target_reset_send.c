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
struct scsi_lun {int dummy; } ;
struct TYPE_2__ {scalar_t__ Status; } ;
struct scsi_cmnd {TYPE_1__ SCp; int /*<<< orphan*/ * host_scribble; } ;
struct bfad_tskim_s {int dummy; } ;
struct bfad_s {int /*<<< orphan*/  bfa; } ;
struct bfad_itnim_s {int /*<<< orphan*/  fcs_itnim; } ;
struct bfa_tskim_s {int dummy; } ;
struct bfa_itnim_s {int dummy; } ;
typedef  int /*<<< orphan*/  scsilun ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_TARGET_RESET_TMO ; 
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BFA_STATUS_FAILED ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  FCP_TM_TARGET_RESET ; 
 int /*<<< orphan*/  KERN_ERR ; 
 struct bfa_itnim_s* bfa_fcs_itnim_get_halitn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 struct bfa_tskim_s* bfa_tskim_alloc (int /*<<< orphan*/ *,struct bfad_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_free (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_start (struct bfa_tskim_s*,struct bfa_itnim_s*,struct scsi_lun,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct scsi_lun*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bfa_status_t
bfad_im_target_reset_send(struct bfad_s *bfad, struct scsi_cmnd *cmnd,
		     struct bfad_itnim_s *itnim)
{
	struct bfa_tskim_s *tskim;
	struct bfa_itnim_s *bfa_itnim;
	bfa_status_t    rc = BFA_STATUS_OK;
	struct scsi_lun scsilun;

	tskim = bfa_tskim_alloc(&bfad->bfa, (struct bfad_tskim_s *) cmnd);
	if (!tskim) {
		BFA_LOG(KERN_ERR, bfad, bfa_log_level,
			"target reset, fail to allocate tskim\n");
		rc = BFA_STATUS_FAILED;
		goto out;
	}

	/*
	 * Set host_scribble to NULL to avoid aborting a task command if
	 * happens.
	 */
	cmnd->host_scribble = NULL;
	cmnd->SCp.Status = 0;
	bfa_itnim = bfa_fcs_itnim_get_halitn(&itnim->fcs_itnim);
	/*
	 * bfa_itnim can be NULL if the port gets disconnected and the bfa
	 * and fcs layers have cleaned up their nexus with the targets and
	 * the same has not been cleaned up by the shim
	 */
	if (bfa_itnim == NULL) {
		bfa_tskim_free(tskim);
		BFA_LOG(KERN_ERR, bfad, bfa_log_level,
			"target reset, bfa_itnim is NULL\n");
		rc = BFA_STATUS_FAILED;
		goto out;
	}

	memset(&scsilun, 0, sizeof(scsilun));
	bfa_tskim_start(tskim, bfa_itnim, scsilun,
			    FCP_TM_TARGET_RESET, BFAD_TARGET_RESET_TMO);
out:
	return rc;
}