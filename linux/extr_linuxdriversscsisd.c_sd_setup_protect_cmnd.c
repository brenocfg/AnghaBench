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
struct scsi_cmnd {int /*<<< orphan*/  prot_flags; TYPE_1__* request; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct bio* bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIP_CTRL_NOCHECK ; 
 int /*<<< orphan*/  BIP_DISK_NOCHECK ; 
 int /*<<< orphan*/  BIP_IP_CHECKSUM ; 
 int /*<<< orphan*/  SCSI_PROT_GUARD_CHECK ; 
 int /*<<< orphan*/  SCSI_PROT_IP_CHECKSUM ; 
 int /*<<< orphan*/  SCSI_PROT_REF_CHECK ; 
 int /*<<< orphan*/  SCSI_PROT_REF_INCREMENT ; 
 int /*<<< orphan*/  SCSI_PROT_TRANSFER_PI ; 
 unsigned int T10_PI_TYPE3_PROTECTION ; 
 int bio_integrity_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_data_dir (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_set_prot_op (struct scsi_cmnd*,unsigned int) ; 
 int /*<<< orphan*/  scsi_set_prot_type (struct scsi_cmnd*,unsigned int) ; 
 int /*<<< orphan*/  sd_prot_flag_mask (unsigned int) ; 
 unsigned int sd_prot_op (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned char sd_setup_protect_cmnd(struct scsi_cmnd *scmd,
					   unsigned int dix, unsigned int dif)
{
	struct bio *bio = scmd->request->bio;
	unsigned int prot_op = sd_prot_op(rq_data_dir(scmd->request), dix, dif);
	unsigned int protect = 0;

	if (dix) {				/* DIX Type 0, 1, 2, 3 */
		if (bio_integrity_flagged(bio, BIP_IP_CHECKSUM))
			scmd->prot_flags |= SCSI_PROT_IP_CHECKSUM;

		if (bio_integrity_flagged(bio, BIP_CTRL_NOCHECK) == false)
			scmd->prot_flags |= SCSI_PROT_GUARD_CHECK;
	}

	if (dif != T10_PI_TYPE3_PROTECTION) {	/* DIX/DIF Type 0, 1, 2 */
		scmd->prot_flags |= SCSI_PROT_REF_INCREMENT;

		if (bio_integrity_flagged(bio, BIP_CTRL_NOCHECK) == false)
			scmd->prot_flags |= SCSI_PROT_REF_CHECK;
	}

	if (dif) {				/* DIX/DIF Type 1, 2, 3 */
		scmd->prot_flags |= SCSI_PROT_TRANSFER_PI;

		if (bio_integrity_flagged(bio, BIP_DISK_NOCHECK))
			protect = 3 << 5;	/* Disable target PI checking */
		else
			protect = 1 << 5;	/* Enable target PI checking */
	}

	scsi_set_prot_op(scmd, prot_op);
	scsi_set_prot_type(scmd, dif);
	scmd->prot_flags &= sd_prot_flag_mask(prot_op);

	return protect;
}