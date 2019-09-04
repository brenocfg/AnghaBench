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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdebug_dev_info {int dummy; } ;
struct scsi_cmnd {int* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INSUFF_RES_ASC ; 
 int /*<<< orphan*/  INSUFF_RES_ASCQ ; 
 int check_condition_result ; 
 int /*<<< orphan*/  get_unaligned_be16 (int*) ; 
 int /*<<< orphan*/  get_unaligned_be32 (int*) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int resp_read_dt0 (struct scsi_cmnd*,struct sdebug_dev_info*) ; 
 int resp_write_dt0 (struct scsi_cmnd*,struct sdebug_dev_info*) ; 
 int resp_xdwriteread (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdebug_dev_info*) ; 
 int /*<<< orphan*/  scsi_bidi_cmnd (struct scsi_cmnd*) ; 

__attribute__((used)) static int resp_xdwriteread_10(struct scsi_cmnd *scp,
			       struct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	u64 lba;
	u32 num;
	int errsts;

	if (!scsi_bidi_cmnd(scp)) {
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		return check_condition_result;
	}
	errsts = resp_read_dt0(scp, devip);
	if (errsts)
		return errsts;
	if (!(cmd[1] & 0x4)) {		/* DISABLE_WRITE is not set */
		errsts = resp_write_dt0(scp, devip);
		if (errsts)
			return errsts;
	}
	lba = get_unaligned_be32(cmd + 2);
	num = get_unaligned_be16(cmd + 7);
	return resp_xdwriteread(scp, lba, num, devip);
}