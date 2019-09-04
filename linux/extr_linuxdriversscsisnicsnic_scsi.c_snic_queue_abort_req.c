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
struct snic_req_info {int /*<<< orphan*/  tm_tag; } ;
struct snic {int /*<<< orphan*/  shost; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*,struct scsi_cmnd*,struct snic_req_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SNIC_TAG_ABORT ; 
 int /*<<< orphan*/  snic_cmd_tag (struct scsi_cmnd*) ; 
 int snic_issue_tm_req (struct snic*,struct snic_req_info*,struct scsi_cmnd*,int) ; 

__attribute__((used)) static int
snic_queue_abort_req(struct snic *snic,
		     struct snic_req_info *rqi,
		     struct scsi_cmnd *sc,
		     int tmf)
{
	SNIC_SCSI_DBG(snic->shost, "q_abtreq: sc %p, rqi %p, tag %x, tmf %d\n",
		      sc, rqi, snic_cmd_tag(sc), tmf);

	/* Add special tag for abort */
	rqi->tm_tag |= SNIC_TAG_ABORT;

	return snic_issue_tm_req(snic, rqi, sc, tmf);
}