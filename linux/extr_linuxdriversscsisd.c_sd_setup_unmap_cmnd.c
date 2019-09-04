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
typedef  int u64 ;
typedef  int u32 ;
struct scsi_device {int /*<<< orphan*/  sector_size; } ;
struct scsi_cmnd {int cmd_len; int* cmnd; unsigned int transfersize; int /*<<< orphan*/  allowed; struct request* request; struct scsi_device* device; } ;
struct TYPE_3__ {unsigned int bv_len; int /*<<< orphan*/  bv_page; scalar_t__ bv_offset; } ;
struct request {int /*<<< orphan*/  timeout; TYPE_1__ special_vec; int /*<<< orphan*/  rq_flags; } ;
struct TYPE_4__ {unsigned int resid_len; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RQF_SPECIAL_PAYLOAD ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 int UNMAP ; 
 int blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  clear_highpage (int /*<<< orphan*/ ) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,char*) ; 
 int scsi_init_io (struct scsi_cmnd*) ; 
 TYPE_2__* scsi_req (struct request*) ; 
 int /*<<< orphan*/  sd_page_pool ; 

__attribute__((used)) static int sd_setup_unmap_cmnd(struct scsi_cmnd *cmd)
{
	struct scsi_device *sdp = cmd->device;
	struct request *rq = cmd->request;
	u64 sector = blk_rq_pos(rq) >> (ilog2(sdp->sector_size) - 9);
	u32 nr_sectors = blk_rq_sectors(rq) >> (ilog2(sdp->sector_size) - 9);
	unsigned int data_len = 24;
	char *buf;

	rq->special_vec.bv_page = mempool_alloc(sd_page_pool, GFP_ATOMIC);
	if (!rq->special_vec.bv_page)
		return BLKPREP_DEFER;
	clear_highpage(rq->special_vec.bv_page);
	rq->special_vec.bv_offset = 0;
	rq->special_vec.bv_len = data_len;
	rq->rq_flags |= RQF_SPECIAL_PAYLOAD;

	cmd->cmd_len = 10;
	cmd->cmnd[0] = UNMAP;
	cmd->cmnd[8] = 24;

	buf = page_address(rq->special_vec.bv_page);
	put_unaligned_be16(6 + 16, &buf[0]);
	put_unaligned_be16(16, &buf[2]);
	put_unaligned_be64(sector, &buf[8]);
	put_unaligned_be32(nr_sectors, &buf[16]);

	cmd->allowed = SD_MAX_RETRIES;
	cmd->transfersize = data_len;
	rq->timeout = SD_TIMEOUT;
	scsi_req(rq)->resid_len = data_len;

	return scsi_init_io(cmd);
}