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
struct snic {scalar_t__ max_tag_id; int /*<<< orphan*/  shost; } ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct scsi_cmnd {struct scsi_device* device; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ snic_cmd_tag (struct scsi_cmnd*) ; 
 int snic_dr_clean_single_req (struct snic*,scalar_t__,struct scsi_device*) ; 
 scalar_t__ snic_is_abts_pending (struct snic*,struct scsi_cmnd*) ; 

__attribute__((used)) static int
snic_dr_clean_pending_req(struct snic *snic, struct scsi_cmnd *lr_sc)
{
	struct scsi_device *lr_sdev = lr_sc->device;
	u32 tag = 0;
	int ret = FAILED;

	for (tag = 0; tag < snic->max_tag_id; tag++) {
		if (tag == snic_cmd_tag(lr_sc))
			continue;

		ret = snic_dr_clean_single_req(snic, tag, lr_sdev);
		if (ret) {
			SNIC_HOST_ERR(snic->shost, "clean_err:tag = %d\n", tag);

			goto clean_err;
		}
	}

	schedule_timeout(msecs_to_jiffies(100));

	/* Walk through all the cmds and check abts status. */
	if (snic_is_abts_pending(snic, lr_sc)) {
		ret = FAILED;

		goto clean_err;
	}

	ret = 0;
	SNIC_SCSI_DBG(snic->shost, "clean_pending_req: Success.\n");

	return ret;

clean_err:
	ret = FAILED;
	SNIC_HOST_ERR(snic->shost,
		      "Failed to Clean Pending IOs on %s device.\n",
		      dev_name(&lr_sdev->sdev_gendev));

	return ret;

}