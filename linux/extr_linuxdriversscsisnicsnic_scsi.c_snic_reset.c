#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hba_reset_fail; } ;
struct TYPE_4__ {TYPE_1__ reset; } ;
struct snic {TYPE_2__ s_stats; int /*<<< orphan*/  snic_lock; int /*<<< orphan*/  ios_inflight; } ;
struct scsi_cmnd {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum snic_state { ____Placeholder_snic_state } snic_state ;

/* Variables and functions */
 int FAILED ; 
 scalar_t__ SNIC_FWRESET ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (struct Scsi_Host*,char*,int) ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (struct Scsi_Host*,char*) ; 
 int /*<<< orphan*/  SNIC_HOST_RESET_TIMEOUT ; 
 int SUCCESS ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 struct snic* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ snic_get_state (struct snic*) ; 
 int snic_issue_hba_reset (struct snic*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  snic_set_state (struct snic*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
snic_reset(struct Scsi_Host *shost, struct scsi_cmnd *sc)
{
	struct snic *snic = shost_priv(shost);
	enum snic_state sv_state;
	unsigned long flags;
	int ret = FAILED;

	/* Set snic state as SNIC_FWRESET*/
	sv_state = snic_get_state(snic);

	spin_lock_irqsave(&snic->snic_lock, flags);
	if (snic_get_state(snic) == SNIC_FWRESET) {
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		SNIC_HOST_INFO(shost, "reset:prev reset is in progres\n");

		msleep(SNIC_HOST_RESET_TIMEOUT);
		ret = SUCCESS;

		goto reset_end;
	}

	snic_set_state(snic, SNIC_FWRESET);
	spin_unlock_irqrestore(&snic->snic_lock, flags);


	/* Wait for all the IOs that are entered in Qcmd */
	while (atomic_read(&snic->ios_inflight))
		schedule_timeout(msecs_to_jiffies(1));

	ret = snic_issue_hba_reset(snic, sc);
	if (ret) {
		SNIC_HOST_ERR(shost,
			      "reset:Host Reset Failed w/ err %d.\n",
			      ret);
		spin_lock_irqsave(&snic->snic_lock, flags);
		snic_set_state(snic, sv_state);
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		atomic64_inc(&snic->s_stats.reset.hba_reset_fail);
		ret = FAILED;

		goto reset_end;
	}

	ret = SUCCESS;

reset_end:
	return ret;
}