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
typedef  scalar_t__ u32 ;
struct snic_req_info {int dummy; } ;
struct snic {scalar_t__ max_tag_id; int /*<<< orphan*/  shost; } ;
struct scsi_device {int dummy; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 scalar_t__ CMD_SP (struct scsi_cmnd*) ; 
 scalar_t__ CMD_STATE (struct scsi_cmnd*) ; 
 scalar_t__ SNIC_IOREQ_ABTS_PENDING ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* scsi_host_find_tag (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * snic_io_lock_tag (struct snic*,scalar_t__) ; 
 int /*<<< orphan*/  snic_ioreq_state_to_str (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
snic_is_abts_pending(struct snic *snic, struct scsi_cmnd *lr_sc)
{
	struct snic_req_info *rqi = NULL;
	struct scsi_cmnd *sc = NULL;
	struct scsi_device *lr_sdev = NULL;
	spinlock_t *io_lock = NULL;
	u32 tag;
	unsigned long flags;

	if (lr_sc)
		lr_sdev = lr_sc->device;

	/* walk through the tag map, an dcheck if IOs are still pending in fw*/
	for (tag = 0; tag < snic->max_tag_id; tag++) {
		io_lock = snic_io_lock_tag(snic, tag);

		spin_lock_irqsave(io_lock, flags);
		sc = scsi_host_find_tag(snic->shost, tag);

		if (!sc || (lr_sc && (sc->device != lr_sdev || sc == lr_sc))) {
			spin_unlock_irqrestore(io_lock, flags);

			continue;
		}

		rqi = (struct snic_req_info *) CMD_SP(sc);
		if (!rqi) {
			spin_unlock_irqrestore(io_lock, flags);

			continue;
		}

		/*
		 * Found IO that is still pending w/ firmware and belongs to
		 * the LUN that is under reset, if lr_sc != NULL
		 */
		SNIC_SCSI_DBG(snic->shost, "Found IO in %s on LUN\n",
			      snic_ioreq_state_to_str(CMD_STATE(sc)));

		if (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING) {
			spin_unlock_irqrestore(io_lock, flags);

			return 1;
		}

		spin_unlock_irqrestore(io_lock, flags);
	}

	return 0;
}