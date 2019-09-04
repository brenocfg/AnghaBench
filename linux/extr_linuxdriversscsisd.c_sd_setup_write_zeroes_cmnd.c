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
typedef  int u64 ;
typedef  int u32 ;
struct scsi_disk {int zeroing_mode; scalar_t__ ws16; } ;
struct scsi_device {scalar_t__ no_write_same; int /*<<< orphan*/  sector_size; } ;
struct scsi_cmnd {struct scsi_device* device; struct request* request; } ;
struct request {int cmd_flags; int /*<<< orphan*/  rq_disk; } ;

/* Variables and functions */
 int BLKPREP_INVALID ; 
 int REQ_NOUNMAP ; 
#define  SD_ZERO_WS10_UNMAP 129 
#define  SD_ZERO_WS16_UNMAP 128 
 int blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 struct scsi_disk* scsi_disk (int /*<<< orphan*/ ) ; 
 int sd_setup_write_same10_cmnd (struct scsi_cmnd*,int) ; 
 int sd_setup_write_same16_cmnd (struct scsi_cmnd*,int) ; 

__attribute__((used)) static int sd_setup_write_zeroes_cmnd(struct scsi_cmnd *cmd)
{
	struct request *rq = cmd->request;
	struct scsi_device *sdp = cmd->device;
	struct scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	u64 sector = blk_rq_pos(rq) >> (ilog2(sdp->sector_size) - 9);
	u32 nr_sectors = blk_rq_sectors(rq) >> (ilog2(sdp->sector_size) - 9);

	if (!(rq->cmd_flags & REQ_NOUNMAP)) {
		switch (sdkp->zeroing_mode) {
		case SD_ZERO_WS16_UNMAP:
			return sd_setup_write_same16_cmnd(cmd, true);
		case SD_ZERO_WS10_UNMAP:
			return sd_setup_write_same10_cmnd(cmd, true);
		}
	}

	if (sdp->no_write_same)
		return BLKPREP_INVALID;

	if (sdkp->ws16 || sector > 0xffffffff || nr_sectors > 0xffff)
		return sd_setup_write_same16_cmnd(cmd, false);

	return sd_setup_write_same10_cmnd(cmd, false);
}