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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct sdebug_dev_info {int dummy; } ;
struct scsi_cmnd {int* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  LBA_OUT_OF_RANGE ; 
 int SDEG_RES_IMMED_MASK ; 
 int SYNCHRONIZE_CACHE ; 
 int check_condition_result ; 
 scalar_t__ get_unaligned_be16 (int*) ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 scalar_t__ get_unaligned_be64 (int*) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sdebug_capacity ; 
 int write_since_sync ; 

__attribute__((used)) static int resp_sync_cache(struct scsi_cmnd *scp,
			   struct sdebug_dev_info *devip)
{
	int res = 0;
	u64 lba;
	u32 num_blocks;
	u8 *cmd = scp->cmnd;

	if (cmd[0] == SYNCHRONIZE_CACHE) {	/* 10 byte cdb */
		lba = get_unaligned_be32(cmd + 2);
		num_blocks = get_unaligned_be16(cmd + 7);
	} else {				/* SYNCHRONIZE_CACHE(16) */
		lba = get_unaligned_be64(cmd + 2);
		num_blocks = get_unaligned_be32(cmd + 10);
	}
	if (lba + num_blocks > sdebug_capacity) {
		mk_sense_buffer(scp, ILLEGAL_REQUEST, LBA_OUT_OF_RANGE, 0);
		return check_condition_result;
	}
	if (!write_since_sync || cmd[1] & 0x2)
		res = SDEG_RES_IMMED_MASK;
	else		/* delay if write_since_sync and IMMED clear */
		write_since_sync = false;
	return res;
}