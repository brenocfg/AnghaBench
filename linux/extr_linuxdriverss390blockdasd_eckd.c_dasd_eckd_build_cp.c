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
struct request {int dummy; } ;
struct TYPE_2__ {int* feature; } ;
struct dasd_eckd_private {unsigned int fcx_max_data; TYPE_1__ features; scalar_t__ uses_cdl; int /*<<< orphan*/  rdc_data; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;
struct dasd_ccw_req {int dummy; } ;
struct dasd_block {unsigned int bp_block; int s2b_shift; struct dasd_device* base; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dasd_ccw_req* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dasd_ccw_req*) ; 
 scalar_t__ READ ; 
 scalar_t__ WRITE ; 
 unsigned int blk_rq_bytes (struct request*) ; 
 int blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 struct dasd_ccw_req* dasd_eckd_build_cp_cmd_single (struct dasd_device*,struct dasd_block*,struct request*,int,int,int,int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 struct dasd_ccw_req* dasd_eckd_build_cp_cmd_track (struct dasd_device*,struct dasd_block*,struct request*,int,int,int,int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 struct dasd_ccw_req* dasd_eckd_build_cp_tpm_track (struct dasd_device*,struct dasd_block*,struct request*,int,int,int,int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ dasd_page_cache ; 
 unsigned int recs_per_track (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 unsigned int sector_div (int,unsigned int) ; 

__attribute__((used)) static struct dasd_ccw_req *dasd_eckd_build_cp(struct dasd_device *startdev,
					       struct dasd_block *block,
					       struct request *req)
{
	int cmdrtd, cmdwtd;
	int use_prefix;
	int fcx_multitrack;
	struct dasd_eckd_private *private;
	struct dasd_device *basedev;
	sector_t first_rec, last_rec;
	sector_t first_trk, last_trk;
	unsigned int first_offs, last_offs;
	unsigned int blk_per_trk, blksize;
	int cdlspecial;
	unsigned int data_size;
	struct dasd_ccw_req *cqr;

	basedev = block->base;
	private = basedev->private;

	/* Calculate number of blocks/records per track. */
	blksize = block->bp_block;
	blk_per_trk = recs_per_track(&private->rdc_data, 0, blksize);
	if (blk_per_trk == 0)
		return ERR_PTR(-EINVAL);
	/* Calculate record id of first and last block. */
	first_rec = first_trk = blk_rq_pos(req) >> block->s2b_shift;
	first_offs = sector_div(first_trk, blk_per_trk);
	last_rec = last_trk =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shift;
	last_offs = sector_div(last_trk, blk_per_trk);
	cdlspecial = (private->uses_cdl && first_rec < 2*blk_per_trk);

	fcx_multitrack = private->features.feature[40] & 0x20;
	data_size = blk_rq_bytes(req);
	if (data_size % blksize)
		return ERR_PTR(-EINVAL);
	/* tpm write request add CBC data on each track boundary */
	if (rq_data_dir(req) == WRITE)
		data_size += (last_trk - first_trk) * 4;

	/* is read track data and write track data in command mode supported? */
	cmdrtd = private->features.feature[9] & 0x20;
	cmdwtd = private->features.feature[12] & 0x40;
	use_prefix = private->features.feature[8] & 0x01;

	cqr = NULL;
	if (cdlspecial || dasd_page_cache) {
		/* do nothing, just fall through to the cmd mode single case */
	} else if ((data_size <= private->fcx_max_data)
		   && (fcx_multitrack || (first_trk == last_trk))) {
		cqr = dasd_eckd_build_cp_tpm_track(startdev, block, req,
						    first_rec, last_rec,
						    first_trk, last_trk,
						    first_offs, last_offs,
						    blk_per_trk, blksize);
		if (IS_ERR(cqr) && (PTR_ERR(cqr) != -EAGAIN) &&
		    (PTR_ERR(cqr) != -ENOMEM))
			cqr = NULL;
	} else if (use_prefix &&
		   (((rq_data_dir(req) == READ) && cmdrtd) ||
		    ((rq_data_dir(req) == WRITE) && cmdwtd))) {
		cqr = dasd_eckd_build_cp_cmd_track(startdev, block, req,
						   first_rec, last_rec,
						   first_trk, last_trk,
						   first_offs, last_offs,
						   blk_per_trk, blksize);
		if (IS_ERR(cqr) && (PTR_ERR(cqr) != -EAGAIN) &&
		    (PTR_ERR(cqr) != -ENOMEM))
			cqr = NULL;
	}
	if (!cqr)
		cqr = dasd_eckd_build_cp_cmd_single(startdev, block, req,
						    first_rec, last_rec,
						    first_trk, last_trk,
						    first_offs, last_offs,
						    blk_per_trk, blksize);
	return cqr;
}