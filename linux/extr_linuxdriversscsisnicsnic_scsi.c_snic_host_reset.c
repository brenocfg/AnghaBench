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
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ u32 ;
struct scsi_cmnd {int /*<<< orphan*/  request; int /*<<< orphan*/ * cmnd; TYPE_1__* device; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FLAGS (struct scsi_cmnd*) ; 
 int FAILED ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (struct Scsi_Host*,char*,struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNIC_TRC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNIC_TRC_CMD (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SNIC_TRC_CMD_STATE_FLAGS (struct scsi_cmnd*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  snic_cmd_tag (struct scsi_cmnd*) ; 
 int snic_reset (struct Scsi_Host*,struct scsi_cmnd*) ; 

int
snic_host_reset(struct scsi_cmnd *sc)
{
	struct Scsi_Host *shost = sc->device->host;
	u32 start_time  = jiffies;
	int ret = FAILED;

	SNIC_SCSI_DBG(shost,
		      "host reset:sc %p sc_cmd 0x%x req %p tag %d flags 0x%llx\n",
		      sc, sc->cmnd[0], sc->request,
		      snic_cmd_tag(sc), CMD_FLAGS(sc));

	ret = snic_reset(shost, sc);

	SNIC_TRC(shost->host_no, snic_cmd_tag(sc), (ulong) sc,
		 jiffies_to_msecs(jiffies - start_time),
		 0, SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));

	return ret;
}