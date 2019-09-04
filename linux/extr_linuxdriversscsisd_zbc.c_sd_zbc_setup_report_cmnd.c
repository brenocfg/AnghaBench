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
struct scsi_disk {TYPE_2__* device; } ;
struct TYPE_3__ {unsigned int length; } ;
struct scsi_cmnd {int cmd_len; scalar_t__ allowed; int /*<<< orphan*/  transfersize; TYPE_1__ sdb; int /*<<< orphan*/  sc_data_direction; int /*<<< orphan*/ * cmnd; struct request* request; } ;
struct request {int /*<<< orphan*/  rq_disk; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  sector_size; } ;

/* Variables and functions */
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ZBC_IN ; 
 int /*<<< orphan*/  ZBC_REPORT_ZONE_PARTIAL ; 
 int /*<<< orphan*/  ZI_REPORT_ZONES ; 
 unsigned int blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct scsi_disk* scsi_disk (int /*<<< orphan*/ ) ; 
 int scsi_init_io (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_is_zoned (struct scsi_disk*) ; 
 int /*<<< orphan*/  sectors_to_logical (TYPE_2__*,int /*<<< orphan*/ ) ; 

int sd_zbc_setup_report_cmnd(struct scsi_cmnd *cmd)
{
	struct request *rq = cmd->request;
	struct scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	sector_t lba, sector = blk_rq_pos(rq);
	unsigned int nr_bytes = blk_rq_bytes(rq);
	int ret;

	WARN_ON(nr_bytes == 0);

	if (!sd_is_zoned(sdkp))
		/* Not a zoned device */
		return BLKPREP_KILL;

	ret = scsi_init_io(cmd);
	if (ret != BLKPREP_OK)
		return ret;

	cmd->cmd_len = 16;
	memset(cmd->cmnd, 0, cmd->cmd_len);
	cmd->cmnd[0] = ZBC_IN;
	cmd->cmnd[1] = ZI_REPORT_ZONES;
	lba = sectors_to_logical(sdkp->device, sector);
	put_unaligned_be64(lba, &cmd->cmnd[2]);
	put_unaligned_be32(nr_bytes, &cmd->cmnd[10]);
	/* Do partial report for speeding things up */
	cmd->cmnd[14] = ZBC_REPORT_ZONE_PARTIAL;

	cmd->sc_data_direction = DMA_FROM_DEVICE;
	cmd->sdb.length = nr_bytes;
	cmd->transfersize = sdkp->device->sector_size;
	cmd->allowed = 0;

	return BLKPREP_OK;
}