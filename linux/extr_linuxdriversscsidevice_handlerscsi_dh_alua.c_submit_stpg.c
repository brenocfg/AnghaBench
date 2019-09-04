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
typedef  unsigned char u8 ;
struct scsi_sense_hdr {int dummy; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_FAILOVER_RETRIES ; 
 int ALUA_FAILOVER_TIMEOUT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int HZ ; 
 unsigned char MAINTENANCE_OUT ; 
 int MAX_COMMAND_SIZE ; 
 unsigned char MO_SET_TARGET_PGS ; 
 int REQ_FAILFAST_DEV ; 
 int REQ_FAILFAST_DRIVER ; 
 int REQ_FAILFAST_TRANSPORT ; 
 unsigned char SCSI_ACCESS_STATE_OPTIMAL ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,unsigned char*) ; 
 int scsi_execute (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,struct scsi_sense_hdr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int submit_stpg(struct scsi_device *sdev, int group_id,
		       struct scsi_sense_hdr *sshdr)
{
	u8 cdb[MAX_COMMAND_SIZE];
	unsigned char stpg_data[8];
	int stpg_len = 8;
	int req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

	/* Prepare the data buffer */
	memset(stpg_data, 0, stpg_len);
	stpg_data[4] = SCSI_ACCESS_STATE_OPTIMAL;
	put_unaligned_be16(group_id, &stpg_data[6]);

	/* Prepare the command. */
	memset(cdb, 0x0, MAX_COMMAND_SIZE);
	cdb[0] = MAINTENANCE_OUT;
	cdb[1] = MO_SET_TARGET_PGS;
	put_unaligned_be32(stpg_len, &cdb[6]);

	return scsi_execute(sdev, cdb, DMA_TO_DEVICE, stpg_data, stpg_len, NULL,
			sshdr, ALUA_FAILOVER_TIMEOUT * HZ,
			ALUA_FAILOVER_RETRIES, req_flags, 0, NULL);
}