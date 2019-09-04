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
struct TYPE_2__ {scalar_t__ typ; } ;
struct snic_tgt {TYPE_1__ tdata; } ;
struct snic {int max_tag_id; int /*<<< orphan*/  shost; } ;
struct scsi_cmnd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*,int,int) ; 
 int SNIC_ITMF_ABTS_TASK ; 
 int SNIC_ITMF_ABTS_TASK_TERM ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ SNIC_TGT_DAS ; 
 int SUCCESS ; 
 struct scsi_cmnd* scsi_host_find_tag (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_target (int /*<<< orphan*/ ) ; 
 struct snic* shost_priv (int /*<<< orphan*/ ) ; 
 int snic_internal_abort_io (struct snic*,struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/ * snic_io_lock_tag (struct snic*,int) ; 
 int /*<<< orphan*/  snic_tgt_to_shost (struct snic_tgt*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct snic_tgt* starget_to_tgt (int /*<<< orphan*/ ) ; 

int
snic_tgt_scsi_abort_io(struct snic_tgt *tgt)
{
	struct snic *snic = NULL;
	struct scsi_cmnd *sc = NULL;
	struct snic_tgt *sc_tgt = NULL;
	spinlock_t *io_lock = NULL;
	unsigned long flags;
	int ret = 0, tag, abt_cnt = 0, tmf = 0;

	if (!tgt)
		return -1;

	snic = shost_priv(snic_tgt_to_shost(tgt));
	SNIC_SCSI_DBG(snic->shost, "tgt_abt_io: Cleaning Pending IOs.\n");

	if (tgt->tdata.typ == SNIC_TGT_DAS)
		tmf = SNIC_ITMF_ABTS_TASK;
	else
		tmf = SNIC_ITMF_ABTS_TASK_TERM;

	for (tag = 0; tag < snic->max_tag_id; tag++) {
		io_lock = snic_io_lock_tag(snic, tag);

		spin_lock_irqsave(io_lock, flags);
		sc = scsi_host_find_tag(snic->shost, tag);
		if (!sc) {
			spin_unlock_irqrestore(io_lock, flags);

			continue;
		}

		sc_tgt = starget_to_tgt(scsi_target(sc->device));
		if (sc_tgt != tgt) {
			spin_unlock_irqrestore(io_lock, flags);

			continue;
		}
		spin_unlock_irqrestore(io_lock, flags);

		ret = snic_internal_abort_io(snic, sc, tmf);
		if (ret < 0) {
			SNIC_HOST_ERR(snic->shost,
				      "tgt_abt_io: Tag %x, Failed w err = %d\n",
				      tag, ret);

			continue;
		}

		if (ret == SUCCESS)
			abt_cnt++;
	}

	SNIC_SCSI_DBG(snic->shost, "tgt_abt_io: abt_cnt = %d\n", abt_cnt);

	return 0;
}